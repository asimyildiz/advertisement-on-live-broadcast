// sfml player
// @author : asým yýldýz

#pragma once

#ifndef __SFMLPLAYER__
#define __SFMLPLAYER__
#pragma warning(disable: 4996)

class SFMLPlayer;


#include "MpegParser.h"
#include "SFMLPopup.h"
#include "AbstractMetaDataService.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>

/**
 * Media Player class
 * Includes all common methods to start playing a ts file
 *
 * play					- plays a ts file, render it frame by frame and displays a popup for pre-defined stream positions
 * close				- close playing of stream and release resources
 */
class SFMLPlayer {  		
	public:		
		SFMLPlayer();
		void play(std::string filename, const AbstractMetaDataService* metaDataService);
		void close();
	private:		
		static const int WINDOW_HEIGHT_MULTIPLIER;
		static const int FRAME_PER_SECONDS;
		static const int PAUSE_PER_FRAME;

		bool _init(std::string filename) const;
		void _draw(AVPicture* frameRGB) const;
		void _listenPopupEvents(sf::Event &event, bool &running) const;
		void _checkServiceAndCreatePopup(const AbstractMetaDataService* metaDataService, SFMLPopup &popup, double &lastPos) const;
		void _renderPopup(SFMLPopup &popup) const;
		
		mutable int _iframeSize;				
		mutable sf::RenderWindow _renderWindow;	
		mutable sf::Sprite _spriteVideo;
		mutable sf::Time _defaultTimeElapsed;
		mutable sf::Uint8* _data;
		MpegParser* _parser;
};

#endif 