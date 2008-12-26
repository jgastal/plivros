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

class AuthorsCollection
{
	public:
		AuthorsCollection(DataBase *db);

		bool insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		bool updateAuthor(Author a) throw(DataBaseException);
		QList<Author> searchAuthors(author_field field, string name);

	private:
		DataBase *db;

		template <class T>
		void updateThemesReference(string table, T data) throw(DataBaseException);
		template <class T>
		void insertThemesReference(string table, T data) throw(DataBaseException);
};

#endif /* AUTHORSCOLLECTION_H_ */
