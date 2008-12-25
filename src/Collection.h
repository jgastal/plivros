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

/**
 * @class Collection Collection.h
 *
 * @brief Class represents a collection of books, authors, publishers and themes
 * stored in a database.
 *
 * This class is used as a high level abstraction of a database containing books,
 * authors, publishers and themes. All it does is convert the objects into SQL
 * statements and send them to a database for storage or retrieval. This database
 * must have a very specific format, as table names and fields are hardcoded.
 */
class Collection
{
	public:
		//TODO Add constructor for collection with a MySQL backend.
		Collection(QString user, bool ro, QString customDbName = "") throw(bad_alloc);
		Collection(QString user, QString customDbName = "") throw(bad_alloc);
		virtual ~Collection() throw();

		bool insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		bool updateBook(Book b) throw(DataBaseException);
		QList<Book> searchBooks(book_field field, string name) throw(DataBaseException);

		bool insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		bool updateAuthor(Author a) throw(DataBaseException);
		QList<Author> searchAuthors(author_field field, string name);

		bool insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		bool updatePublisher(Publisher p) throw(DataBaseException);
		QList<Publisher> searchPublishers(publisher_field field, string name);

		bool insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		bool updateTheme(Theme t) throw(DataBaseException);
		QList<Theme> searchThemes(theme_field field, string name);

	private:
		DataBase *db;
		QString user;
		QString dbName;
		bool readOnly;

		template <class T>
		void updateThemesReference(string table, T data) throw(DataBaseException);
		void updateAuthorsReference(Book b) throw(DataBaseException);
		void updatePublishersReference(Book b) throw(DataBaseException);
		template <class T>
		void insertThemesReference(string table, T data) throw(DataBaseException);
		void insertAuthorsReference(Book b) throw(DataBaseException);
		void insertPublishersReference(Book b) throw(DataBaseException);
		template <class Type, class Reference>
		void insertReference(string type, Type data, string refType, Reference r) throw(DataBaseException);
		bool genericDelete(unsigned int id, string type) throw(DataBaseException);
};

#endif /* COLLECTION_H_ */
