/**
 * @file Collection.h
 *
 * @date Nov 4, 2008
 * @author Jonas M. Gastal
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <QtCore/QList>

#include "ResultSet.h"

#include "Book.h"
#include "Author.h"
#include "Theme.h"
#include "Publisher.h"

class DataBase;

class Collection
{
	public:
		Collection(QString user, bool ro, QString customDbName = "");
		Collection(QString user, QString customDbName = "");

		bool insertBook(Book &b);
		bool deleteBook(unsigned int id);
		Book updateBook(unsigned int id, Book b);
		QList<Book> searchBooks(book_field field, QString name);

		bool insertAuthor(Author &a);
		bool deleteAuthor(unsigned int id);
		Author updateAuthor(unsigned int id, Author a);
		QList<Author> searchAuthors(author_field field, QString name);

		bool insertPublisher(Publisher &p);
		bool deletePublisher(unsigned int id);
		Publisher updatePublisher(unsigned int id, Publisher p);
		QList<Publisher> searchPublishers(publisher_field field, QString name);

		bool insertTheme(Theme &t) throw(bad_alloc,SQLiteException);
		bool deleteTheme(unsigned int id) throw(SQLiteException);
		Theme updateTheme(unsigned int id, Theme t) throw(SQLiteException);
		QList<Theme> searchThemes(theme_field field, QString name);

	private:
		DataBase *db;
		QString user;
		QString dbName;
		bool readOnly;
};

#endif /* COLLECTION_H_ */
