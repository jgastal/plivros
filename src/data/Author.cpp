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
 * @file Author.cpp
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#include <QString>
#include <QList>
#include <QCoreApplication>

#include "Author.h"
#include "Theme.h"
#include "DataObject.h"

const char* Author::headers[] = {
	QT_TRANSLATE_NOOP("Author", "First Name"),
	QT_TRANSLATE_NOOP("Author", "Last Name"),
	QT_TRANSLATE_NOOP("Author", "Description"),
	QT_TRANSLATE_NOOP("Author", "Critique"),
	QT_TRANSLATE_NOOP("Author", "Rating"),
	QT_TRANSLATE_NOOP("Author", "Picture"),
	QT_TRANSLATE_NOOP("Author", "Themes")
};
const unsigned short int Author::propertiesCount = 7;

Author::Author() : DataObject("", 0)
{
	setFirstName("");
	setLastName("");
	setCritique("");
	setRating(0);
	setPicture("");
	setThemes(QList<Theme>());
}

Author::Author(QString fn, QString ln, QString desc, QString cri,
	unsigned short int rat, QString pic, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setFirstName(fn);
	setLastName(ln);
	setCritique(cri);
	setRating(rat);
	setPicture(pic);
	setThemes(t);
}

QString Author::getFirstName() const
{
	return firstName;
}

void Author::setFirstName(QString firstName)
{
	this->firstName = firstName;
}

QString Author::getLastName() const
{
	return lastName;
}

void Author::setLastName(QString lastName)
{
	this->lastName = lastName;
}

QString Author::getName() const
{
	return QString(lastName + ", " + firstName);
}

QString Author::getCritique() const
{
	return critique;
}

void Author::setCritique(QString critique)
{
	this->critique = critique;
}

unsigned short int Author::getRating() const
{
	return rating;
}

void Author::setRating(unsigned short int rating)
{
	this->rating = rating;
}

QString Author::getPicture() const
{
	return picture;
}

void Author::setPicture(QString picture)
{
	this->picture = picture;
}

QList<Theme> Author::getThemes() const
{
	return themes;
}

QString Author::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName()).append("; ");
	return str;
}

void Author::setThemes(QList<Theme> themes)
{
	this->themes = themes;
}

bool Author::operator==(const Author a) const
{
	if(firstName == a.getFirstName() && getLastName() == a.getLastName() &&
		getDescription() == a.getDescription() && getCritique() == a.getCritique()
		&& getRating() == a.getRating() && getPicture() == a.getPicture() &&
		getThemes() == a.getThemes() && getId() == a.getId())
		return true;
	return false;
}

QStringList Author::getProperties() const
{
	QStringList prop;
	prop << getFirstName() << getLastName() << getDescription() << getCritique();
	prop << QString::number(getRating()) << getPicture() << getThemesNames();
	return prop;
}

Author::author_field Author::getHeader(unsigned short int i)
{
	switch(i)
	{
		case a_firstname:
			return a_firstname;
		case a_lastname:
			return a_lastname;
		case a_description:
			return a_description;
		case a_critique:
			return a_critique;
		case a_rating:
			return a_rating;
		case a_picture:
			return a_picture;
		case a_themes:
			return a_themes;
	}
}

QStringList Author::getHeaders()
{
	QStringList ret;
	for(int i = 0; i < propertiesCount; i++)
		ret << QCoreApplication::translate("Author", headers[i]);
	return ret;
}
