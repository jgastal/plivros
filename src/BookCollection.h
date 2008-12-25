/**
 * @file BookCollection.h
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#ifndef BOOKCOLLECTION_H_
#define BOOKCOLLECTION_H_

#include "DataBaseException.h"

class DataBase;

class BookCollection
{
	public:
		BookCollection(DataBase *db);

		bool insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		bool updateBook(Book b) throw(DataBaseException);
		QList<Book> searchBooks(book_field field, string name) throw(DataBaseException);

	private:
		DataBase *db;

		template <class T>
		void updateThemesReference(string table, T data) throw(DataBaseException);
		void updateAuthorsReference(Book b) throw(DataBaseException);
		void updatePublishersReference(Book b) throw(DataBaseException);
		template <class T>
		void insertThemesReference(string table, T data) throw(DataBaseException);
		void insertAuthorsReference(Book b) throw(DataBaseException);
		void insertPublishersReference(Book b) throw(DataBaseException);
		QList<Book> parseBookResultSet(ResultSet rs);
};

#endif /* BOOKCOLLECTION_H_ */
