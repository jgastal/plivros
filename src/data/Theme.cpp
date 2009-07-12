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
 * @file Theme.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <QString>
#include <QCoreApplication>

#include "Theme.h"
#include "DataObject.h"

const char *Theme::headers[] = {
	QT_TRANSLATE_NOOP("Theme", "Name"),
	QT_TRANSLATE_NOOP("Theme", "Description")
};
const unsigned short int Theme::propertiesCount = 2;

Theme::Theme() : DataObject("", 0)
{
	setName("");
}

Theme::Theme(QString nm, QString desc, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
}

QString Theme::getName() const
{
	return name;
}

void Theme::setName(const QString name)
{
	this->name = name;
}

bool Theme::operator==(const Theme &t) const
{
	if(getName() == t.getName() && getDescription() == t.getDescription() && getId() == t.getId())
		return true;
	return false;
}

QStringList Theme::getProperties() const
{
	QStringList prop;
	prop << getName() << getDescription();
	return prop;
}

Theme::theme_field Theme::getHeader(unsigned short int i)
{
	switch(i)
	{
		case t_name:
			return t_name;
		case t_description:
			return t_description;
	}
}

QStringList Theme::getHeaders()
{
	QStringList ret;
	for(int i = 0; i < propertiesCount; i++)
		ret << QCoreApplication::translate("Theme", headers[i]);
	return ret;
}
