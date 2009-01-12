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
class BookCollection;
class AuthorCollection;
class PublisherCollection;
class ThemeCollection;

/**
 * @class Collection Collection.h
 *
 * @brief Class represents a collection of books, authors, publishers and themes
 * stored in a database.
 *
 * @warning No relational integrity check is performed on add, therefore it is
 * possible to add book referencing a non existing theme, be carefull!
 *
 * @todo Add relational integrity checking.
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
		Collection(QString u, QString customDbName = "", bool ro = false) throw(bad_alloc);
		virtual ~Collection() throw();

		bool insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		bool updateBook(Book b) throw(DataBaseException);
		QList<Book> searchBooks(Book::book_field field, string name) throw(DataBaseException);

		bool insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		bool updateAuthor(Author a) throw(DataBaseException);
		QList<Author> searchAuthors(Author::author_field field, string name);

		bool insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		bool updatePublisher(Publisher p) throw(DataBaseException);
		QList<Publisher> searchPublishers(Publisher::publisher_field field, string name);

		bool insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		bool updateTheme(Theme t) throw(DataBaseException);
		QList<Theme> searchThemes(Theme::theme_field field, string name);

	private:
		DataBase *db;
		BookCollection *bc;
		AuthorCollection *ac;
		PublisherCollection *pc;
		ThemeCollection *tc;
		QString user;
		QString dbName;
		bool readOnly;

		void updateThemeReference(Book b);
		void updateThemeReference(Author a);
		void updateThemeReference(Publisher p);
		template <class t>
		void updateAuthorReference(t data, string type);
		template <class t>
		void updatePublisherReference(t data, string type);
		PreparedStatement compositeSearchBooks(Book::book_field field, string name) throw(DataBaseException);
		QList<Book> parseBookResultSet(ResultSet &rs) throw(DataBaseException);
		QList<Author> getBooksAuthors(int id) throw(DataBaseException);
		QList<Publisher> getBooksPublishers(int id) throw(DataBaseException);
		QList<Theme> getBooksThemes(int id) throw(DataBaseException);
		Author getBooksTranslator(int id) throw(DataBaseException);
};

#endif /* COLLECTION_H_ */
