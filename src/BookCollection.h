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

#include "DataBaseException.h"
#include "Book.h"

class BookCollection
{
	public:
		BookCollection(DataBase *db) throw();

		void insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		void updateBook(Book b) throw(DataBaseException);
		QList<Book> searchBooks(book_field field, string name) throw(DataBaseException);

	private:
		DataBase *db;
		QList<Book> bookList; //Last search result

		void updateThemesReference(Book b) throw(DataBaseException);
		void updateAuthorsReference(Book b) throw(DataBaseException);
		void updatePublishersReference(Book b) throw(DataBaseException);
		void insertThemesReference(Book b) throw(DataBaseException);
		void insertAuthorsReference(Book b) throw(DataBaseException);
		void insertPublishersReference(Book b) throw(DataBaseException);
		QList<Book> parseBookResultSet(ResultSet rs);
};

#endif /* BOOKCOLLECTION_H_ */
