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
 * @file PublisherCollection.h
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHERCOLLECTION_H_
#define PUBLISHERCOLLECTION_H_

#include <QtCore/QList>

#include "Publisher.h"
#include "DataBaseException.h"

class DataBase;

class PublisherCollection
{
	public:
		PublisherCollection(DataBase *db) throw();

		void insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		void updatePublisher(Publisher p) throw(DataBaseException);

	private:
		DataBase *db;
};

#endif /* PUBLISHERCOLLECTION_H_ */
