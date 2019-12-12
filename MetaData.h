// popup
// @author : asým yýldýz

#pragma once

#ifndef __METADATA__
#define __METADATA__

class MetaData;

#include <string>

/**
 * Meta Data class
 * Defines a meta data object
 */
class MetaData
{
	public:	
		MetaData() {};
		MetaData(double startPos, double endPos, std::wstring message, std::string url);

		double startPos;
		double endPos;
		std::wstring message;
		std::string url;
};

#endif