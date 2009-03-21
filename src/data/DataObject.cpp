#include "DataObject.h"

#include <QString>

unsigned short int DataObject::propertiesCount = 0;
QStringList DataObject::headers = QStringList();

DataObject::DataObject(const QString desc, const unsigned int id)
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

QString DataObject::getDescription() const
{
	return description;
}

void DataObject::setDescription(const QString description)
{
	this->description = description;
}
