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
 * @file Publisher.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <QString>
#include <QList>

#include "Publisher.h"
#include "Theme.h"
#include "DataObject.h"

const QStringList Publisher::headers = QStringList() << QT_TR_NOOP("Name") <<
QT_TR_NOOP("Description") << QT_TR_NOOP("Critique") << QT_TR_NOOP("Logo") << QT_TR_NOOP("Themes");
const unsigned short int Publisher::propertiesCount = 5;

Publisher::Publisher() : DataObject("", 0)
{
	setName("");
	setCritique("");
	setLogo("");
	setThemes(QList<Theme>());
}

Publisher::Publisher(QString nm, QString desc, QString cri, QString logo, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
	setCritique(cri);
	setLogo(logo);
	setThemes(t);
}

QString Publisher::getName() const
{
	return name;
}

void Publisher::setName(QString name)
{
	this->name = name;
}

QString Publisher::getCritique() const
{
	return critique;
}

void Publisher::setCritique(QString critique)
{
	this->critique = critique;
}

QString Publisher::getLogo() const
{
	return logo;
}

void Publisher::setLogo(QString logo)
{
	this->logo = logo;
}

QList<Theme> Publisher::getThemes() const
{
	return themes;
}

QString Publisher::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName()).append("; ");
	return str;
}

void Publisher::setThemes(QList<Theme> themes)
{
	this->themes = themes;
}

bool Publisher::operator==(const Publisher p) const
{
	if(getName() == p.getName() && getDescription() == p.getDescription() &&
		getCritique() == p.getCritique() && getLogo() == p.getLogo() &&
		getThemes() == p.getThemes() && getId() == p.getId())
		return true;
	return false;
}

QStringList Publisher::getProperties() const
{
	QStringList prop;
	prop << getName() << getDescription() <<  getCritique() << getLogo();
	prop << getThemesNames();
	return prop;
}

Publisher::publisher_field Publisher::getHeader(unsigned short int i)
{
	switch(i)
	{
		case p_name:
			return p_name;
		case p_description:
			return p_description;
		case p_critique:
			return p_critique;
		case p_logo:
			return p_logo;
		case p_themes:
			return p_themes;
	}
}

/*void Publisher::initHeaders()
{
	Publisher::headers << QT_TR_NOOP("Name") << QT_TR_NOOP("Description");
	Publisher::headers << QT_TR_NOOP("Critique") << QT_TR_NOOP("Logo") << QT_TR_NOOP("Themes");
	Publisher::propertiesCount = 5;
}*/
