#include "MetaData.h"

/**
 * MetaData class constructor  
 * Object to store metadata information which will be displayed when a stream position is hit
 *
 * @param startPos	starting position of the stream where we would like to display message
 * @param endPos	end position of the stream where we stop displaying message
 * @param message	message to be displayed on screen
 * @param url		url to redirect user when clicked on message
 */
MetaData::MetaData(double startPos, double endPos, std::wstring message, std::string url) {
	this->startPos = startPos;
	this->endPos = endPos;
	this->message = message;
	this->url = url;
}