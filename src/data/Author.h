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
 * @file Author.h
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <QString>
#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

class Author : public DataObject
{
	public:
		Author();
		Author(QString fn, QString ln, QString desc, QString cri,
			unsigned short int rat, QString pic, QList<Theme> t,
			unsigned int id = 0);
		QString getFirstName() const;
		void setFirstName(QString);
		QString getLastName() const;
		void setLastName(QString);
		QString getName() const;
		QString getCritique() const;
		void setCritique(QString);
		unsigned short int getRating() const;
		void setRating(unsigned short int);
		QString getPicture() const;
		void setPicture(QString);
		QList<Theme> getThemes() const;
		QString getThemesNames() const;
		void setThemes(QList<Theme> themes);
		QStringList getProperties() const;
		bool operator==(const Author a) const;

		enum author_field
		{
			a_firstname,
			a_lastname,
			a_description,
			a_critique,
			a_rating,
			a_picture,
			a_themes
		};
		static author_field getHeader(unsigned short int i);
		static const QStringList headers;
		static const unsigned short int propertiesCount;

	private:
		QString firstName;
		QString lastName;
		QString critique;
		unsigned short int rating;
		QString picture; //path to picture of author
		QList<Theme> themes; //List of themes
};

#endif /* AUTHOR_H_ */
