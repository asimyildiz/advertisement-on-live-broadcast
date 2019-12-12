// popup
// @author : asým yýldýz

#pragma once

#ifndef __SFMLPOPUP__
#define __SFMLPOPUP__

class SFMLPopup;


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

/**
 * Popup class
 * Displays a popup on top of SFML window
 *
 * draw				- draws a popup on top of SFML window at specified position
 * show				- displays the drawn popup
 * hide				- hides the displayed (drawn) popup
 * setMessage		- set message on current popup
 * setMousePosition	- set mouse position for a mouse event
 */
class SFMLPopup {  		
	public:		
		SFMLPopup(int mainWidth, int mainHeight);

		bool isHidden();
		void reDisplay();
		void draw(sf::RenderWindow &window);
		void show();
		void hide();        

		void setMessage(std::wstring message);
		void setMousePosition(float posX, float posY);	
    private:
		static const float POPUP_DEFAULT_XPOS;
		static const float POPUP_DEFAULT_YPOS;
		static const float POPUP_DEFAULT_WIDTH;
		static const float POPUP_DEFAULT_HEIGHT;
		static const float POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT;
		static const float POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT;
		static const float POPUP_DEFAULT_MESSAGE_PADDING;		

		bool _isHidden;
        sf::RectangleShape _background;			
		sf::RectangleShape _icon;				
		sf::RectangleShape _closeButton;		
		
		sf::Texture _textureIcon;
		sf::Texture _textureClose;
		sf::Texture _textureDialog;
		sf::Text _textureMessage;
		sf::Font _font;
		
		std::wstring _message;
		sf::Vector2f _mousePosition;

		void _setPopupBackground(int screenWidth);
		void _setPopupDialog();
		void _setPopupCloseButton();
		void _setPopupStyling();
		void _update();
		void _close();
};


#endif 