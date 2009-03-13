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
