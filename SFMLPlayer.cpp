#include "SFMLPlayer.h"

const int SFMLPlayer::WINDOW_HEIGHT_MULTIPLIER = 4;
const int SFMLPlayer::FRAME_PER_SECONDS = 25;

/**
 * constructor of SFMLPlayer class
 * create an mpegparser using FFMPEG library
 */
SFMLPlayer::SFMLPlayer() 
{
	this->_parser = new MpegParser();	
}

/**
 * play a ts file using ffmpeg
 * parse and decode video frame by frame using ffmpeg 
 * check current frame and position, then display a popup with a message on top of stream for defined timeframe
 *
 * @param filename ts file path
 * @param metaDataService to find active message information to display on popup for a stream position
 */
void SFMLPlayer::play(std::string filename, const AbstractMetaDataService* metaDataService)
{
	if (this->_init(filename))
	{		
		SFMLPopup popup(this->_parser->getWidth(), this->_parser->getHeight());

		sf::Event event;		
		double lastPos = 0.f;
		bool running = true;
		while (running)
		{
			this->_listenPopupEvents(event, running);
			if (this->_parser->readStream())
			{
				this->_checkServiceAndCreatePopup(metaDataService, popup, lastPos);
				this->_renderPopup(popup);
			}
			else {
				running = false;
			}
		}
	}
}

/**
 * listen popup events such as closed, keypress, escape
 *
 * @param event				current event from windows
 * @param running			if application needs to be terminated after this event
 */
void SFMLPlayer::_listenPopupEvents(sf::Event &event, bool &running) const {
	while (this->_renderWindow.pollEvent(event))
	{
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
			running = false;
		}
	}
}

/**
 * check current frame and position, 
 * check if we have a metadata defined for this position
 * set message of the popup using the message from current metadata object
 *
 * @param metaDataService	service object to fetch meta data
 * @param popup		popup object to display some information on top of player
 * @param lastPos	last decoded stream position
 * @param isDialogClosed if dialog is already closed, do not try to re-display it
 */
void SFMLPlayer::_checkServiceAndCreatePopup(const AbstractMetaDataService* metaDataService, SFMLPopup &popup, double &lastPos) const {
	if (this->_parser->getCurrentPosition() != lastPos) {
		lastPos = this->_parser->getCurrentPosition();
		const bool hasMetaData = metaDataService->hasMetaData(lastPos);
		if (hasMetaData && !popup.isHidden()) {
			popup.setMessage(metaDataService->getMessage(lastPos));
			popup.setMousePosition((float)sf::Mouse::getPosition(this->_renderWindow).x, (float)sf::Mouse::getPosition(this->_renderWindow).y);
			popup.show();
		}
		else if (!hasMetaData) {
			popup.hide();
			popup.reDisplay();
		}
	}
}

/**
 * render current popup on top of player (active window)
 *
 * @param popup	popup object to display information on top of video
 */
void SFMLPlayer::_renderPopup(SFMLPopup &popup) const {
	this->_renderWindow.clear();
	this->_draw(this->_parser->getCurrentFrame());
	popup.draw(this->_renderWindow);
	this->_renderWindow.display();
}

/**
 * close a stream and free FFMPEG parser resources
 */
void SFMLPlayer::close()
{
	this->_parser->close();
	this->_renderWindow.close();
}

/**
 * init player
 * get width and height information from stream
 * create and render a window based for player
 *
 * @param filename name of the ts file to open
 * @return true if a window to play stream is created successfully if not return false
 */
bool SFMLPlayer::_init(std::string filename) const
{
	if (this->_parser->open(filename) && this->_parser->initStream()) {
		int width = this->_parser->getWidth();
		int height = this->_parser->getHeight();

		this->_iframeSize = width * height * (SFMLPlayer::WINDOW_HEIGHT_MULTIPLIER - 1);
		this->_data = new sf::Uint8[width * height * SFMLPlayer::WINDOW_HEIGHT_MULTIPLIER];

		this->_renderWindow.create(sf::VideoMode(width, height, 32), "");		
		this->_renderWindow.setFramerateLimit(SFMLPlayer::FRAME_PER_SECONDS);
		return true;
	}
	this->_parser->close();
	return false;
}

/**
 * draw a stream frame to window
 *
 * @param frameRGB current frame to be displayed
 */
void SFMLPlayer::_draw(AVPicture *frameRGB) const
{
	if (frameRGB == NULL) {
		return;
	}
	
	sf::Texture texture;
	texture.create(this->_parser->getWidth(), this->_parser->getHeight());
	texture.update(frameRGB->data[0]);
	this->_spriteVideo.setTexture(texture);		
	this->_renderWindow.draw(this->_spriteVideo);
}