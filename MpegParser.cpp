#include "MpegParser.h"

/**
 * MpegParser class constructor
 * Registers to all muxers, demuxers and protocols of ffmepg
 * Allocates memory for ffmpeg object
 */
MpegParser::MpegParser()
{
	av_register_all();
	this->_formatContext = avformat_alloc_context();
}

/**
 * open broadcast (ts) file to parse using ffmpeg
 *
 * @param filename	path of the ts file to parse
 * @return true if file can be opened successfully, false if not
 */
bool MpegParser::open(std::string filename) {
	this->_errorCode = avformat_open_input(&this->_formatContext, filename.c_str(), NULL, NULL);
	if (this->_errorCode == 0) {
		return true;
	}
	this->_printCurrentFFMpegError();
	return false;
}

/**
 * prints current ffmpeg error which is stored inside _errorCode to stderr
 */
void MpegParser::_printCurrentFFMpegError() const {
	char errorMessageBuffer[AV_ERROR_MAX_STRING_SIZE];
	av_strerror(this->_errorCode, errorMessageBuffer, sizeof(errorMessageBuffer));
	fprintf(stderr, "Error occurred: %s\n", errorMessageBuffer);
}

/**
 * start parsing a stream
 * check if file is a valid stream, if it has a video to be parsed
 * check if video has a valid codec to parse
 * start parsing the video from it's first buffer
 * 
 * @return true if successfully started parsing
 */
bool MpegParser::initStream() {

	if (!this->_hasValidStream()) {
		fprintf(stderr, "There is no valid stream to parse\n");
		return false;
	}

	this->_initStreamAndCodecs();
	if (!this->_hasValidCodec()) {
		fprintf(stderr, "There is no valid codec for stream\n");
		return false;
	}

	this->_calculateFrameRate();
	this->_initFrame();
	if (!this->_hasValidInitialFrame()) {
		fprintf(stderr, "Cannot allocate memory for initial frame\n");
		return false;
	}

	this->_drawFrame();

	av_init_packet(&this->_currentPacket);
	this->_isVideoLoaded = true;
	return true;
}

/**
 * check if this is a valid stream
 * check if we have a stream information
 * check if we have more at least 1 stream inside the parser and if it's type is video 
 *
 * @return true if stream is valid
 */
bool MpegParser::_hasValidStream() {
	if (avformat_find_stream_info(this->_formatContext, NULL) < 0)
	{
		this->_freeStream();
		return false;
	}

	this->_videoStreamIndex = -1;
	for (size_t i = 0; i < this->_formatContext->nb_streams; i++)
	{
		if (this->_formatContext->streams[i]->codec->coder_type == AVMEDIA_TYPE_VIDEO)
		{
			this->_videoStreamIndex = i;
			break;
		}
	}

	if (this->_videoStreamIndex == -1) {
		this->_freeStream();
		return false;
	}

	return true;
}

/**
 * select active video stream 
 * select active video context for stream
 * select active codec using codec id from ffmpeg video context
 */
void MpegParser::_initStreamAndCodecs() {
	this->_stream = this->_formatContext->streams[this->_videoStreamIndex];
	this->_codecContext = this->_stream->codec;
	this->_codecContext->codec = avcodec_find_decoder(this->_codecContext->codec_id);
}

/**
 * check if this is a valid codec
 * check if we can start using active codec from avcodec library 
 *
 * @return true if codec is valid
 */
bool MpegParser::_hasValidCodec() {
	if (this->_codecContext->codec == NULL)
	{
		this->_freeStream();
		return false;
	}
	else if (avcodec_open2(this->_codecContext, this->_codecContext->codec, NULL) != 0)
	{
		this->_freeStream();
		return false;
	}

	return true;
}

/**
 * unused method
 * method to calculate actual frame rate from stream
 * this can be used to put a delay while getting next frame data 
 */
void MpegParser::_calculateFrameRate() {
	AVRational rationalAverageFrameRate = this->_stream->avg_frame_rate;
	AVRational rationalFrameRate = this->_stream->r_frame_rate;
	if ((!rationalAverageFrameRate.num || !rationalAverageFrameRate.den) && (!rationalFrameRate.num || !rationalFrameRate.den))
	{
		fprintf(stderr, "Unable to get video frame rate, using 25fps \n");		
		this->_videoFrameRate = 1.f / 25;
	}
	else
	{
		if (rationalAverageFrameRate.num && rationalAverageFrameRate.den) {
			this->_videoFrameRate = 1.f / ((float)rationalAverageFrameRate.num / rationalAverageFrameRate.den);
		}
		else {
			this->_videoFrameRate = 1.f / ((float)rationalFrameRate.num / rationalFrameRate.den);
		}
	}
}

/**
 * allocate memory for frame
 * allocate memory for RGB frame
 * initialize current frame number to 0
 */
void MpegParser::_initFrame() {
	this->_frame = av_frame_alloc();
	this->_frameRGB = av_frame_alloc();	
}

/**
 * check if initial frame is successfully 
 * check if we have a stream information
 * check if we have more at least 1 stream inside the parser and if it's type is video
 *
 * @return true if stream is valid
 */
bool MpegParser::_hasValidInitialFrame() {
	if (!this->_frame || !this->_frameRGB)
	{
		this->_freeStream();
		return false;
	}

	return true;
}

/**
 * draw current frame by using avpicture
 * allocate memory for active frame
 * draw the frame using it's rgb value
 */
void MpegParser::_drawFrame() {
	int numBytes = avpicture_get_size(AV_PIX_FMT_RGBA, this->_codecContext->width, this->_codecContext->height);
	uint8_t* buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
	avpicture_fill((AVPicture *)this->_frameRGB, buffer, AV_PIX_FMT_RGBA, this->_codecContext->width, this->_codecContext->height);
}

/**
 * read a frame into packet
 * if packet is read successfully, start decoding the packet
 * if packet is decoded, set current frame position and then draw image for current frame position 
 *
 * @return true if image is decoded and drawn successfully
 */
bool MpegParser::readStream() {
	if (this->_isVideoLoaded) {
		if (this->_readCurrentPacket()) {
			int frameFinished = 0;
			avcodec_decode_video2(this->_codecContext, this->_frame, &frameFinished, &this->_currentPacket);
			if (frameFinished)
			{
				this->_setCurrentFramePosition();
				this->_drawImageFromCurrentFramePosition();
			}
			return true;
		}		
	}

	return false;	
}

/**
 * read frame into packet 
 *
 * @return true if frame is read into packet
 */
bool MpegParser::_readCurrentPacket() {
	do
	{
		av_free_packet(&this->_currentPacket);
		int result = av_read_frame(this->_formatContext, &this->_currentPacket);
		if (result < 0)
		{
			return false;
		}
	} while (this->_currentPacket.stream_index != this->_videoStreamIndex);
	
	return true;
}

/**
 * set current position to decoded packet's position
 */
void MpegParser::_setCurrentFramePosition() {
	this->_currentPosition = 0;
	if (this->_currentPacket.dts != AV_NOPTS_VALUE)
	{
		this->_currentPosition = static_cast<double>(this->_currentPacket.dts);
	}
	this->_currentPosition *= av_q2d(this->_codecContext->time_base);
}

/**
 * draw image using current frame
 */
void MpegParser::_drawImageFromCurrentFramePosition() {
	SwsContext* imageContext = sws_getCachedContext(NULL, this->_codecContext->width, this->_codecContext->height, this->_codecContext->pix_fmt, this->_codecContext->width, this->_codecContext->height, AV_PIX_FMT_RGBA, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	sws_scale(imageContext, this->_frame->data, this->_frame->linesize, 0, this->_frame->height, this->_frameRGB->data, this->_frameRGB->linesize);
}

/**
 * close current decoding stream
 * free current stream object
 */
void MpegParser::close() {
	this->_freeStream();
}

/**
 * free current frame and RGB frame
 * free current codec context
 */
void MpegParser::_freeStream() {
	av_free_packet(&this->_currentPacket);
	av_frame_free(&this->_frame);
	av_frame_free(&this->_frameRGB);
	avcodec_close(this->_codecContext);
	avcodec_free_context(&this->_codecContext);
	this->_isVideoLoaded = false;
}

/**
 * getter for current frame
 *
 * @return current frame
 */
AVPicture* MpegParser::getCurrentFrame() const
{
	if (this->_frameRGB == NULL) {
		return NULL;
	}		
	return (AVPicture *)this->_frameRGB;
}

/**
 * getter for frame rate information of stream
 *
 * @return frame rate of stream
 */
float MpegParser::getFrameRate() const
{
	return static_cast<float>(av_q2d(av_guess_frame_rate(this->_formatContext, this->_stream, nullptr)));
}

/**
 * getter for width of stream
 *
 * @return width of stream
 */
int MpegParser::getWidth() const
{
	if (this->_codecContext == NULL) {
		return 0;
	}
	return this->_codecContext->width;
}

/**
 * getter for height of stream
 *
 * @return height of stream
 */
int MpegParser::getHeight() const
{
	if (this->_codecContext == NULL) {
		return 0;
	}
	return this->_codecContext->height;
}

/**
 * getter for duration of stream
 *
 * @return duration of stream
 */
int64_t MpegParser::getDuration() const
{		
	if (this->_formatContext == NULL) {
		return 0;
	}
	return this->_formatContext->duration;			
}

/**
 * getter for current position of decoded stream
 *
 * @return current position of decoded stream
 */
double MpegParser::getCurrentPosition() const
{
	return this->_currentPosition;
}