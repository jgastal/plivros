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
 * @file Publisher.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <QString>
#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

class Publisher : public DataObject
{
	public:
		Publisher();
		Publisher(QString nm, QString desc, QString cri, QString logo, QList<Theme> t,
			unsigned int id = 0);
		QString getName() const;
		void setName(QString name);
		QString getCritique() const;
		void setCritique(QString critique);
		QString getLogo() const;
		void setLogo(QString logo);
		QList<Theme> getThemes() const;
		QString getThemesNames() const;
		void setThemes(QList<Theme> themes);
		bool operator==(const Publisher p) const;
		QStringList getProperties() const;

		enum publisher_field
		{
			p_name,
			p_description,
			p_critique,
			p_logo,
			p_themes
		};
		static publisher_field getHeader(unsigned short int i);
		static const QStringList headers;
		static const unsigned short int propertiesCount;

	private:
		QString name;
		QString critique;
		QString logo;
		QList<Theme> themes;
};

#endif /* PUBLISHER_H_ */
