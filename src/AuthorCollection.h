/**
 * @file AuthorsCollection.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef AUTHORSCOLLECTION_H_
#define AUTHORSCOLLECTION_H_

class DataBase;

#include "DataBaseException.h"
#include "Author.h"

class AuthorCollection
{
	public:
		AuthorCollection(DataBase *db);

		void insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		void updateAuthor(Author a) throw(DataBaseException);
		QList<Author> searchAuthors(author_field field, string name);

	private:
		DataBase *db;

		void updateThemesReference(Author a) throw(DataBaseException);
		void insertThemesReference(Author a) throw(DataBaseException);
};

#endif /* AUTHORSCOLLECTION_H_ */
