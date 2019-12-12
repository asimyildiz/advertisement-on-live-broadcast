#include "MetaDataFactory.h"

/**
 * MetaDataFactory class constructor
 * Factory pattern implementation to decide which algorithm is going to be used to fetch metadata information
 *
 * @param type		which algorithm to use
 */
MetaDataFactory::MetaDataFactory(int type) {
	if (type == 1) {
		this->_metaDataService = new FakeMetaDataService();
	}else {
		this->_metaDataService = NULL;
	}
}

/**
 * MetaDataFactory class destructor 
 */
MetaDataFactory::~MetaDataFactory() {
	if (this->_metaDataService)
	{
		delete[] this->_metaDataService;
		this->_metaDataService = NULL;
	}
}

/**
 * getter for active metaDataService object used to fetch data
 * @return initialized metaDataService object
 */
AbstractMetaDataService* MetaDataFactory::getMetaDataService() const {
	return this->_metaDataService;
}