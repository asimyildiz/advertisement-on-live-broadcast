// popup
// @author : asým yýldýz

#pragma once

#ifndef __METADATAFACTORY__
#define __METADATAFACTORY__

class MetaDataFactory;


#include "FakeMetaDataService.h"

/**
 * Meta Data Factory class
 * Decide on which meta data service class to fetch meta data
 * For now there is only a fake meta data service implementation
 */
class MetaDataFactory {
public:
	MetaDataFactory(int type);
	~MetaDataFactory();

	AbstractMetaDataService* getMetaDataService() const;
private:
	AbstractMetaDataService *_metaDataService;
};

#endif