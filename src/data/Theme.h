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
 * @file Theme.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef THEME_H_
#define THEME_H_

#include "DataObject.h"

#include <QString>
#include <QStringList>

class Theme : public DataObject
{
	public:
		Theme();
		Theme(QString nm, QString desc, unsigned int id = 0);
		QString getName() const;
		void setName(const QString name);
		bool operator==(const Theme &t) const;
		QStringList getProperties() const;

		enum theme_field
		{
			t_name,
			t_description
		};
		static theme_field getHeader(unsigned short int i);
		static const QStringList headers;
		static const unsigned short int propertiesCount;

	private:
		QString name;
} ;

#endif /* THEME_H_ */
