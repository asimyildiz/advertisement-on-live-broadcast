// popup
// @author : asým yýldýz

#pragma once

#ifndef __ABSTRACTMETADATASERVICE__
#define __ABSTRACTMETADATASERVICE__

class AbstractMetaDataService;


#include "MetaData.h"
#include <algorithm>
#include <vector>

/**
 * Abstract meta data service class
 * Includes all common method implementations and definition of virtual methods for MetaDataService classes
 * For now only fake implementation exists, 
 *  other implementations such as get metadata from a http service, 
 *  or from a file can be implemented later on, and only factory method can be updated
 * 
 * getMetaData			- get meta data from a http service, or from a file, or from an array-inline
 * hasMetaData			- check if we have a metadata defined for a stream position
 * getUrl				- get url information (site to be visited) from the meta data object for a stream position
 * getMessage			- get message information to be displayed to the user from the meta data object for a stream position
 */
class AbstractMetaDataService {
	public:
		virtual void getMetaData(std::string path) = 0;
		bool hasMetaData(double pos) const;
		std::string getUrl(double pos) const;
		std::wstring getMessage(double pos) const;
	protected:
		std::vector<MetaData> _metaDataList;
	private:
		MetaData _findMetaData(double pos) const;
};

#endif