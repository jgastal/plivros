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
