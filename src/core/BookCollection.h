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
 * @file BookCollection.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef BOOKCOLLECTION_H_
#define BOOKCOLLECTION_H_

class DataBase;
class ResultSet;

#include <QtCore/QList>

#include "PreparedStatement.h"
#include "DataBaseException.h"
#include "Book.h"

class BookCollection
{
	public:
		BookCollection(DataBase *db) throw();

		void insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		void updateBook(Book b) throw(DataBaseException);

	private:
		DataBase *db;
};

#endif /* BOOKCOLLECTION_H_ */
