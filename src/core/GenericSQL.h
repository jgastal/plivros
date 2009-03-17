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

#include "DataObject.h"
#include "Book.h"

void updateReference(string type, DataObject *data, string refType, DataBase db) throw(DataBaseException);

void insertReference(Book &b, string refType, DataBase *db) throw(DataBaseException);
void insertReference(Author &a, DataBase *db) throw(DataBaseException);
void insertReference(Publisher &p, DataBase *db) throw(DataBaseException);

void deleteReference(string type, unsigned int id, string refType, DataBase *db) throw(DataBaseException);
unsigned int genericDelete(unsigned int id, string type, DataBase *db) throw(DataBaseException);

#endif /* GENERICSQL_H_ */
