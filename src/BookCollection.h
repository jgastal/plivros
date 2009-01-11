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
		QList<Book> searchBooks(Book::book_field field, string name) throw(DataBaseException);

	private:
		DataBase *db;
		QList<Book> bookList; //Last search result

		PreparedStatement compositeSearchBooks(Book::book_field field, string name) throw(DataBaseException);
		QList<Book> parseBookResultSet(ResultSet &rs) throw(DataBaseException);

		QList<Author> getBooksAuthors(int id) throw(DataBaseException);
		Author getBooksTranslator(int id) throw(DataBaseException);
		QList<Publisher> getBooksPublishers(int id) throw(DataBaseException);
		QList<Theme> getBooksThemes(int id) throw(DataBaseException);
};

#endif /* BOOKCOLLECTION_H_ */
