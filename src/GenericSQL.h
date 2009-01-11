/**
 * @file GenericSQL.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef GENERICSQL_H_
#define GENERICSQL_H_

#include <string>

#include "DataBase.h"
#include "DataBaseException.h"

#include "Book.h"

template <class Type>
void updateReference(string type, Type data, string refType, DataBase db) throw(DataBaseException);

void insertReference(Book data, string refType, DataBase *db) throw(DataBaseException);
void insertReference(Author data, DataBase *db) throw(DataBaseException);
void insertReference(Publisher data, DataBase *db) throw(DataBaseException);

void deleteReference(string type, unsigned int id, string refType, DataBase *db) throw(DataBaseException);
unsigned int genericDelete(unsigned int id, string type, DataBase *db) throw(DataBaseException);

#endif /* GENERICSQL_H_ */
