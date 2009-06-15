/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file Collection.h
 *
 * @date Nov 4, 2008
 * @author Jonas M. Gastal
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <QList>
#include <QString>
#include <QObject>

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
class Collection : public QObject
{
	Q_OBJECT

	public:
		Collection(QString u, QString customDbName = "", bool ro = false) throw(bad_alloc);
		Collection(QString h, QString u, QString p, QString n, bool ro = false) throw(bad_alloc);
		virtual ~Collection() throw();

		bool insertBook(Book &b) throw(DataBaseException);
		bool deleteBook(unsigned int id) throw(DataBaseException);
		bool updateBook(Book b) throw(DataBaseException);
		QList<Book> searchBooks(Book::book_field field, QString name) throw(DataBaseException);

		bool insertAuthor(Author &a) throw(DataBaseException);
		bool deleteAuthor(unsigned int id) throw(DataBaseException);
		bool updateAuthor(Author a) throw(DataBaseException);
		QList<Author> searchAuthors(Author::author_field field, QString name);

		bool insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		bool updatePublisher(Publisher p) throw(DataBaseException);
		QList<Publisher> searchPublishers(Publisher::publisher_field field, QString name) throw(DataBaseException);

		bool insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		bool updateTheme(Theme t) throw(DataBaseException);
		QList<Theme> searchThemes(Theme::theme_field field, QString name) throw(DataBaseException);

	signals:
		///@brief Emited when a book is inserted in this collection.
		void bookInserted();
		///@brief Emited when a book is deleted in this collection.
		void bookDeleted();
		///@brief Emited when a book is updated in this collection.
		void bookUpdated();
		///@brief Emited when any change in the books table of this collection occurs.
		void booksChanged();
		///@brief Emited when an author is inserted in this collection.
		void authorInserted();
		///@brief Emited when an author is deleted in this collection.
		void authorDeleted();
		///@brief Emited when an author is updated in this collection.
		void authorUpdated();
		///@brief Emited when any change in the authors table of this collection occurs.
		void authorsChanged();
		///@brief Emited when a publisher is inserted in this collection.
		void publisherInserted();
		///@brief Emited when a publisher is delete in this collection.
		void publisherDeleted();
		///@brief Emited when a publisher is updated in this collection.
		void publisherUpdated();
		///@brief Emited when any change in the publishers table of this collection occurs.
		void publishersChanged();
		///@brief Emited when a theme is inserted in this collection.
		void themeInserted();
		///@brief Emited when a theme is deleted in this collection.
		void themeDeleted();
		///@brief Emited when a theme is updated in this collection.
		void themeUpdated();
		///@brief Emited when any change in the themes table of this collection occurs.
		void themesChanged();

	private:
		DataBase *db;
		BookCollection *bc;
		AuthorCollection *ac;
		PublisherCollection *pc;
		ThemeCollection *tc;
		QString user;
		QString dbName;
		bool readOnly;

		void initConnects();

		//private methods to deal with references
		void updateThemeReference(Book b) throw(DataBaseException);
		void updateThemeReference(Author a) throw(DataBaseException);
		void updateThemeReference(Publisher p) throw(DataBaseException);
		template <class t>
		void updateAuthorReference(t data, QString type) throw(DataBaseException);
		template <class t>
		void updatePublisherReference(t data, QString type) throw(DataBaseException);

		//private methods to deal with book search
		PreparedStatement simpleSearchBooks(Book::book_field field, QString name) throw(DataBaseException);
		PreparedStatement compositeSearchBooks(Book::book_field field, QString name) throw(DataBaseException);
		QList<Book> parseBookResultSet(ResultSet &rs) throw(DataBaseException);
		QList<Author> getBooksAuthors(int id) throw(DataBaseException);
		QList<Publisher> getBooksPublishers(int id) throw(DataBaseException);
		QList<Theme> getBooksThemes(int id) throw(DataBaseException);
		Author getBooksTranslator(int id) throw(DataBaseException);

		//private methods to deal with author search
		PreparedStatement simpleSearchAuthors(Author::author_field field, QString name) throw(DataBaseException);
		PreparedStatement compositeSearchAuthors(Author::author_field field, QString name) throw(DataBaseException);
		QList<Author> parseAuthorResultSet(ResultSet &rs) throw(DataBaseException);
		QList<Theme> getAuthorsThemes(int id) throw(DataBaseException);

		//private methods to deal with publisher search
		PreparedStatement simpleSearchPublishers(Publisher::publisher_field field, QString name) throw(DataBaseException);
		PreparedStatement compositeSearchPublishers(Publisher::publisher_field field, QString name) throw(DataBaseException);
		QList<Publisher> parsePublisherResultSet(ResultSet &rs) throw(DataBaseException);
		QList<Theme> getPublishersThemes(int id) throw(DataBaseException);

		//private methods to deal with theme search
		QList<Theme> parseThemeResultSet(ResultSet &rs) throw(DataBaseException);
};

#endif /* COLLECTION_H_ */
