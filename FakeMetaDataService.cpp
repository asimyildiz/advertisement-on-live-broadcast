#include "FakeMetaDataService.h"

/**
 * get meta data from fake data
 *
 * @param path - path of the file for file service or url for http service, empty for fake service
 */
void FakeMetaDataService::getMetaData(std::string path) {
	this->_metaDataList.push_back(MetaData(27580000, 27635000, L"If you are interested in this VW \n Press OK and we will call you.", "http://fakeaddress.com/?customer=CUSTOMER_1"));
	this->_metaDataList.push_back(MetaData(27645000, 30000000, L"Press OK in order to list \n and buy these items.", "http://fakeaddress.com/?customer=CUSTOMER_1"));
}