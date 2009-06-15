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
 * @file ThemeCollection.h
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#ifndef THEMECOLLECTION_H_
#define THEMECOLLECTION_H_

#include <QtCore/QList>

#include "Theme.h"
#include "DataBaseException.h"

class DataBase;

class ThemeCollection
{
	public:
		ThemeCollection(DataBase *db) throw();

		void insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		void updateTheme(Theme t) throw(DataBaseException);

	private:
		DataBase *db;
};

#endif /* THEMECOLLECTION_H_ */
