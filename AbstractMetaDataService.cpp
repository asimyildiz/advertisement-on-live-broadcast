#include "AbstractMetaDataService.h"

/**
 * check if we have a metadata defined for a broadcast stream position
 *
 * @param pos position to search inside current broadcast stream
 * @return true if metadata exists for a broadcast stream position
 */
bool AbstractMetaDataService::hasMetaData(double pos) const {
	auto it = find_if(this->_metaDataList.begin(), this->_metaDataList.end(), [pos](const MetaData& metaData)
		{ 
			return (metaData.startPos <= pos && metaData.endPos > pos); 
		});

	return (it != this->_metaDataList.end());
}

/**
 * get url information(site to be visited) from the meta data object for a broadcast stream position
 *
 * @param pos position to search inside current broadcast stream
 * @return url data of the metadata object that exists for a broadcast stream position
 */
std::string AbstractMetaDataService::getUrl(double pos) const {
	MetaData currentMetaData = this->_findMetaData(pos);
	return currentMetaData.url;	
}

/**
 * get message information to be displayed to the user from the meta data object for a broadcast stream position
 *
 * @param pos position to search inside current broadcast stream
 * @return message data of the metadata object that exists for a broadcast stream position
 */
std::wstring AbstractMetaDataService::getMessage(double pos) const {
	MetaData currentMetaData = this->_findMetaData(pos);
	return currentMetaData.message;
}

/**
 * find meta data for a position inside current broadcast stream
 *
 * @param pos position to search inside current broadcast stream
 * @return the metadata object if it exists for a broadcast stream position
 */
MetaData AbstractMetaDataService::_findMetaData(double pos) const {
	auto it = find_if(this->_metaDataList.begin(), this->_metaDataList.end(), [pos](const MetaData& metaData)
	{
		return (metaData.startPos <= pos && metaData.endPos > pos);
	});
	if (it != this->_metaDataList.end())
	{
		auto index = std::distance(this->_metaDataList.begin(), it);
		return this->_metaDataList[index];
	}
	return MetaData();
}
		