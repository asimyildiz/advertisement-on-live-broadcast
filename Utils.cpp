#include "Utils.h"

/**
 * converts a string to wstring
 *
 * @param stringToConvert String value to convert to wstring
 * @return converted wstring value
 */
std::wstring Utils::convertStringToWstring(const std::string& stringToConvert)
{
	if (stringToConvert.empty()) {
		return std::wstring(L"");
	}

	int size = MultiByteToWideChar(CP_UTF8, 0, &stringToConvert[0], (int)stringToConvert.size(), NULL, 0);
	if (size) {
		std::wstring convertedWstring(size, 0);
		MultiByteToWideChar(CP_UTF8, 0, &stringToConvert[0], (int)stringToConvert.size(), &convertedWstring[0], size);
		return convertedWstring;
	}
	
	return std::wstring(L"");
}