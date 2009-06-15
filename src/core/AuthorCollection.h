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
 * @file AuthorCollection.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef AUTHORSCOLLECTION_H_
#define AUTHORSCOLLECTION_H_

class DataBase;

#include <QtCore/QList>

#include "DataBaseException.h"
#include "Author.h"

class AuthorCollection
{
	public:
		AuthorCollection(DataBase *db) throw();

		void insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		void updateAuthor(Author a) throw(DataBaseException);

	private:
		DataBase *db;
};

#endif /* AUTHORSCOLLECTION_H_ */
