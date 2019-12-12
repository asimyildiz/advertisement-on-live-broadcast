// popup
// @author : asým yýldýz

#pragma once

#ifndef __FAKEMETADATASERVICE__
#define __FAKEMETADATASERVICE__

class FakeMetaDataService;


#include "AbstractMetaDataService.h"

/**
 * Fake meta data service class
 * Define and populate a vector of fake MetaData
 *
 * getMetaData			- get meta data from a http service, or from a file, or from an array-inline
 */
class FakeMetaDataService : public AbstractMetaDataService {
public:
	void getMetaData(std::string path);
};

#endif