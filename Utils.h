// application
// @author : ASIM YILDIZ

#pragma once

#ifndef __UTILS__
#define __UTILS__

class Utils;

/**
 * Implementation of utility methods 
 *
 * convertStringToWstring - converts a string to wstring 
 */
class Utils
{
public:
	static std::wstring convertStringToWstring(const std::string& stringToConvert);
};

#endif