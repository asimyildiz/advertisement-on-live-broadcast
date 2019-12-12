#include "SFMLPopup.h"

const float SFMLPopup::POPUP_DEFAULT_XPOS = 200.f;
const float SFMLPopup::POPUP_DEFAULT_YPOS = 0.f;
const float SFMLPopup::POPUP_DEFAULT_WIDTH = 250.f;
const float SFMLPopup::POPUP_DEFAULT_HEIGHT = 150.f;
const float SFMLPopup::POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT = 20.f;
const float SFMLPopup::POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT = 20.f;
const float SFMLPopup::POPUP_DEFAULT_MESSAGE_PADDING = 20.f;

/**
 * constructor of SFMLPopup class
 * create and initialize a popup
 */
SFMLPopup::SFMLPopup(int screenWidth, int screenHeight)
{
	this->_setPopupBackground(screenWidth);
	this->_setPopupDialog();
	this->_setPopupCloseButton();
	this->_setPopupStyling();
	this->_isHidden = false;
}

/**
 * define and set popup background and outline borader color
 * @param screenWidth	used to calculate current ypos of popup
 */
void SFMLPopup::_setPopupBackground(int screenWidth) {
	this->_background.setSize(sf::Vector2f(POPUP_DEFAULT_WIDTH, POPUP_DEFAULT_HEIGHT));
	this->_background.setPosition(screenWidth - POPUP_DEFAULT_WIDTH, POPUP_DEFAULT_YPOS);
	this->_background.setFillColor(sf::Color(100, 0, 0, 150));
	this->_background.setOutlineColor(sf::Color::White);
	this->_background.setOutlineThickness(2.f);
}

/**
 * define and set popup dialog box 
 */
void SFMLPopup::_setPopupDialog() {
	if (!this->_textureDialog.loadFromFile("icons/dialog.png"))
	{
		std::cerr << "Could not load your icon!!!" << std::endl;
		std::cout << "Icon must be 20 x 20 pixels, or strange behavior will occur" << std::endl;
	}
	this->_icon.setSize(sf::Vector2f(POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT, POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT));
	this->_icon.setTexture(&this->_textureDialog);
	this->_icon.setPosition(POPUP_DEFAULT_XPOS + POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT, POPUP_DEFAULT_YPOS + POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT);
}

/**
 * define and set popup close button
 */
void SFMLPopup::_setPopupCloseButton() {
	if (!this->_textureClose.loadFromFile("icons/close.png"))
	{
		std::cerr << "Could not load your icon!!!" << std::endl;
		std::cout << "Icon must be 20 x 20 pixels, or strange behavior will occur" << std::endl;
	}
	this->_closeButton.setSize(sf::Vector2f(POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT, POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT));
	this->_closeButton.setTexture(&this->_textureClose);
	this->_closeButton.setPosition(POPUP_DEFAULT_XPOS + POPUP_DEFAULT_WIDTH - (2 * this->_closeButton.getGlobalBounds().width), POPUP_DEFAULT_YPOS);
}

/**
 * define and set popup styling
 */
void SFMLPopup::_setPopupStyling() {
	if (!this->_font.loadFromFile("fonts/Aller_Rg.ttf"))
	{
		std::cerr << "Could not load font file!!!" << std::endl;
	}

	this->_textureMessage.setFont(this->_font);
	this->_textureMessage.setString("");
	this->_textureMessage.setCharacterSize(16);
	this->_textureMessage.setColor(sf::Color::White);
	this->_textureMessage.setPosition(POPUP_DEFAULT_XPOS + POPUP_DEFAULT_MESSAGE_PADDING, this->_icon.getPosition().y + this->_icon.getGlobalBounds().height + POPUP_DEFAULT_MESSAGE_PADDING);
}

/**
 * draw popup on sfml window
 * 
 * @param window	window object where we draw the popup
 */
void SFMLPopup::draw(sf::RenderWindow &window)
{
	this->_update();
	window.draw(this->_background);
	window.draw(this->_icon);
	window.draw(this->_closeButton);
	window.draw(this->_textureMessage);
}

/**
 * update text, position etc before drawing the popup on screen
 */
void SFMLPopup::_update()
{
	this->_close();
	float mainX = this->_background.getPosition().x,
		mainY = this->_background.getPosition().y;

	this->_icon.setPosition(mainX + POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT, mainY + POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT);
	this->_closeButton.setPosition(mainX + this->_background.getGlobalBounds().width - (2 * this->_closeButton.getGlobalBounds().width), mainY);
	this->_textureMessage.setString(this->_message);
	this->_textureMessage.setPosition(mainX + POPUP_DEFAULT_MESSAGE_PADDING, this->_icon.getPosition().y + this->_icon.getGlobalBounds().height + POPUP_DEFAULT_MESSAGE_PADDING);
}

/**
 * always check mouse click positions in order to understand if close button is pressed
 * if close button is pressed, hide popup and set isHidden state of this popup to true 
 */
void SFMLPopup::_close()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if ((this->_mousePosition.x < this->_closeButton.getPosition().x + this->_closeButton.getGlobalBounds().width
			&& this->_mousePosition.x > this->_closeButton.getPosition().x
			&& this->_mousePosition.y < this->_closeButton.getPosition().y + this->_closeButton.getGlobalBounds().height
			&& this->_mousePosition.y > this->_closeButton.getPosition().y))
		{			
			this->hide();
			this->_isHidden = true;
		}
	}
}

/**
 * resize popup window and icon sizes to actual values in order to display it
 */
void SFMLPopup::show()
{
	this->_background.setSize(sf::Vector2f(POPUP_DEFAULT_WIDTH, POPUP_DEFAULT_HEIGHT));
	this->_icon.setSize(sf::Vector2f(POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT, POPUP_DEFAULT_BUTTON_WIDTH_HEIGHT));
	this->_closeButton.setSize(sf::Vector2f(POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT, POPUP_DEFAULT_CLOSE_BUTTON_WIDTH_HEIGHT));
}

/**
 * clear texts and resize popup and icon sizes to 0 in order to hide it
 */
void SFMLPopup::hide()
{
	this->_message = std::wstring();
	this->_background.setSize(sf::Vector2f(0, 0));
	this->_icon.setSize(sf::Vector2f(0, 0));
	this->_closeButton.setSize(sf::Vector2f(0, 0));
}

/**
 * set popup hidden state to false, so that it can be displayed
 */
void SFMLPopup::reDisplay() {
	this->_isHidden = false;
}

/**
 * getter for popup's hidden state
 *
 * @return true if popup is in hidden state
 */
bool SFMLPopup::isHidden() {
	return this->_isHidden;
}

/**
 * setter for popup message 
 */
void SFMLPopup::setMessage(std::wstring message) { 
	this->_message = message; 
};

/**
 * setter for mouse position
 */
void SFMLPopup::setMousePosition(float posX, float posY) { 
	this->_mousePosition = sf::Vector2f(posX, posY); 
};