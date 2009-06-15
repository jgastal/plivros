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
 * @file GenericSQL.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef GENERICSQL_H_
#define GENERICSQL_H_

#include <QString>

#include "DataBase.h"
#include "DataBaseException.h"

#include "DataObject.h"
#include "Book.h"

void updateReference(QString type, DataObject *data, QString refType, DataBase db) throw(DataBaseException);

void insertReference(Book &b, QString refType, DataBase *db) throw(DataBaseException);
void insertReference(Author &a, DataBase *db) throw(DataBaseException);
void insertReference(Publisher &p, DataBase *db) throw(DataBaseException);

void deleteReference(QString type, unsigned int id, QString refType, DataBase *db) throw(DataBaseException);
unsigned int genericDelete(unsigned int id, QString type, DataBase *db) throw(DataBaseException);

#endif /* GENERICSQL_H_ */
