/**
 * @file AuthorsCollection.h
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
