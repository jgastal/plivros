#include "DataObject.h"

#include <string>

using namespace std;

DataObject::DataObject(const string desc, const unsigned int id)
{
	setDescription(desc);
	this->id = id;
}

unsigned int DataObject::getId() const
{
	return id;
}

void DataObject::setId(const unsigned int id)
{
	if(this->id == 0) //If id has never been set.
		this->id = id;
}

string DataObject::getDescription() const
{
	return description;
}

void DataObject::setDescription(const string description)
{
	this->description = description;
}

unsigned short int DataObject::getPropertiesCount() const
{
	return propertiesCount;
}

void DataObject::setPropertiesCount(unsigned short int c)
{
	this->propertiesCount = c;
}

QStringList DataObject::getHeaders() const
{
	return headers;
}
