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
		Collection(QString user, bool ro, QString customDbName = "") throw(bad_alloc);
		Collection(QString user, QString customDbName = "") throw(bad_alloc);
		virtual ~Collection() throw();

		bool insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		bool updateBook(unsigned int id, Book b) throw(DataBaseException);
		QList<Book> searchBooks(book_field field, QString name);

		bool insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		bool updateAuthor(unsigned int id, Author a) throw(DataBaseException);
		QList<Author> searchAuthors(author_field field, QString name);

		bool insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		bool updatePublisher(unsigned int id, Publisher p) throw(DataBaseException);
		QList<Publisher> searchPublishers(publisher_field field, QString name);

		bool insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		bool updateTheme(unsigned int id, Theme t) throw(DataBaseException);
		QList<Theme> searchThemes(theme_field field, QString name);

	private:
		DataBase *db;
		QString user;
		QString dbName;
		bool readOnly;

		template <class T>
		void updateThemesReference(string table, T data);
		template <class T>
		void insertThemesReference(string table, T data);
		bool genericDelete(unsigned int id, string type);
};

#endif /* COLLECTION_H_ */
