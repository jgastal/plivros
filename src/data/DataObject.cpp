/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file DataObject.cpp
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

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
