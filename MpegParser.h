// mpeg parser
// @author : asým yýldýz

#pragma once

#ifndef __MPEGPARSER__
#define __MPEGPARSER__
#pragma warning(disable: 4996)

/**
 * Mpeg parser class
 * Parses broadcast (ts file) using ffmpeg
 * !Warnings supressed for deprecated methods 
 */
class MpegParser;

#include <fstream>

extern "C"
{
	#include <libavcodec\avcodec.h>
	#include <libavdevice\avdevice.h>
	#include <libavfilter\avfilter.h>
	#include <libavformat\avformat.h>
	#include <libavutil\avutil.h>
	#include <libswscale\swscale.h>
}

class MpegParser {  		
	public:		
		MpegParser();
		bool open(std::string filename);
		bool initStream();
		bool readStream();
		void close();

		AVPicture* getCurrentFrame() const;
		float getFrameRate() const;
		int getWidth() const;
		int getHeight() const;
		int64_t getDuration() const;    		
		double getCurrentPosition() const;				
	private:
		void _printCurrentFFMpegError() const;
		bool _hasValidStream();
		bool _hasValidCodec();
		bool _hasValidInitialFrame();
		void _initStreamAndCodecs();
		void _initFrame();
		void _calculateFrameRate();
		void _drawFrame();
		bool _readCurrentPacket();
		void _setCurrentFramePosition();		
		void _drawImageFromCurrentFramePosition();
		void _freeStream();		

		double _currentPosition;
		int _errorCode;
		int _videoStream;
		int _videoStreamIndex;
		float _videoFrameRate;
		bool _isVideoLoaded;
		AVPacket _currentPacket;
		AVFormatContext* _formatContext;
		AVCodecContext* _codecContext;
		AVFrame* _frame, *_frameRGB;		
		AVStream* _stream;				
};

#endif 