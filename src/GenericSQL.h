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

template <class Type, class Reference>
void updateReference(string type, Type data, string refType, DataBase db) throw(DataBaseException);
template <class Type, class Reference>
void insertReference(string type, Type data, string refType, DataBase db) throw(DataBaseException);
void deleteReference(string type, unsigned int id, string refType, DataBase db) throw(DataBaseException);
unsigned int genericDelete(unsigned int id, string table, DataBase db) throw(DataBaseException);

#endif /* GENERICSQL_H_ */
