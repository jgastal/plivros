/**
 * @file Collection.cpp
 *
 * @date Nov 4, 2008
 * @author Jonas M. Gastal
 */

#include <QtCore/QString>

#include "DataBase.h"
#include "ResultSet.h"
#include "DataBaseException.h"
#include "PreparedStatement.h"

#include "Collection.h"
#include "BookCollection.h"
#include "AuthorCollection.h"
#include "PublisherCollection.h"
#include "ThemeCollection.h"
#include "GenericSQL.h"

using namespace std;

/**
 * @brief Opens the database associated with this collection. Creating a new
 * one if it didn't exist.
 *
 * @param u The name of the user to whom this collection belongs.
 * @param ro If the database should be opened read only.
 * @param customDbName Name to be used for the database file, if empty user name
 * will be used.
 */
Collection::Collection(QString u, QString customDbName, bool ro) throw(bad_alloc)
{
	readOnly = ro;
	user = u;
	if(customDbName != "") //this obviously means empty names are not valid
		dbName = customDbName;
	else
		dbName = u.append(".db");

	db = new DataBase(dbName.toStdString());
	bc = new BookCollection(db);
	ac = new AuthorCollection(db);
	pc = new PublisherCollection(db);
	tc = new ThemeCollection(db);
}

///@brief Closes database.
Collection::~Collection() throw()
{
	delete db;
	delete bc;
}

/**
 * @brief Add book \a b to the collection.
 *
 * @param b Book to be added.
 *
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warning If the collection was opened as read only does nothing and returns false.
 * @warning Make sure you DON'T SET the books id before calling this method.
 *
 * This methods adds \a b to the database sets its id and insert the references
 * made to authors, publishers and themes.
 */
bool Collection::insertBook(Book &b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->insertBook(b);
	insertReferenceBook(b, "theme", db);
	insertReferenceBook(b, "author", db);
	insertReferenceBook(b, "publisher", db);

	return true;
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Deletes every author, publisher and theme reference to the book and the book
 * itself.
 */
bool Collection::deleteBook(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	deleteReference("book", id, "theme", db);
	deleteReference("book", id, "author", db);
	deleteReference("book", id, "publisher", db);
	return bc->deleteBook(id);
}

/**
 * @brief Updates book.
 *
 * @param b Book to be updated.
 *
 * @return Whether the operation was successful.
 *
 * Update every field of the book except the id but including the referenced
 * author, publishers and authors.
 */
bool Collection::updateBook(Book b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->updateBook(b);
	updateAuthorReference(b, "book");
	updatePublisherReference(b, "book");
	updateThemeReference(b);

	return true;
}

QList<Book> Collection::searchBooks(Book::book_field field, string name) throw(DataBaseException)
{
	return bc->searchBooks(field, name);
}

/**
 * @brief Add Author \a a to the collection.
 *
 * @param a Author to be added.
 *
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warning If the collection was opened as read only does nothing and returns false.
 * @warning Make sure you DON'T SET the authors id before calling this method.
 *
 * This method adds both the author and the theme references it makes to the
 * database. The id of the author is set.
 */
bool Collection::insertAuthor(Author &a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->insertAuthor(a); //inserts author
	insertReferenceAuthor(a, db); //insert author/theme references

	return true;
}

/**
 * @brief Deletes author from collection.
 *
 * @param id ID of author to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Deletes both the referenced themes and the author.
 */
bool Collection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	deleteReference("author", id, "theme", db);
	return ac->deleteAuthor(id);
}

/**
 * @brief Updates author.
 *
 * @param a Author to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method updates all fields of the author except the id bu including the
 * themes references.
 */
bool Collection::updateAuthor(Author a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->updateAuthor(a);
	updateThemeReference(a);

	return true;
}

/**
 * @brief Adds publisher \a p to the collection.
 *
 * @param p Publisher to be added.
 *
 * @return Whether the operation was successful.
 *
 * This method adds the publisher and all associated references to the DataBase
 * and then sets the publishers id.
 */
bool Collection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->insertPublisher(p);
	insertReferencePublisher(p, db);

	return true;
}

/**
 * @brief Removes publisher from collection.
 *
 * @param id ID of publisher to be removed.
 *
 * @return Whether operation was successful.
 *
 * Deletes any theme references to this publisher and the publisher itself.
 */
bool Collection::deletePublisher(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;

	deleteReference("publisher", id, "theme", db);
	return pc->deletePublisher(id);
}

/**
 * @brief Updates publisher.
 *
 * @param p Publisher to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method update every field of the publisher except the id but including
 * referenced mehtods.
 */
bool Collection::updatePublisher(Publisher p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->updatePublisher(p);
	updateThemeReference(p);

	return true;
}

/**
 * @brief Adds theme \a t to the collection.
 *
 * @param t The theme to be inserted.
 *
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warning If the collection was opened as read only does nothing and returns false.
 * @warning Make sure you DON'T SET the books id before calling this method.
 *
 * The function creates a SQL insert statement based on the given theme, executes
 * the statement then sets the id given by the database in the theme and returns
 * success.
 */
bool Collection::insertTheme(Theme &t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	tc->insertTheme(t);

	return true;
}

/**
 * @brief Removes a theme from the collection.
 *
 * @param id ID of theme to be removed.
 *
 * @return Whether the operation was successful.
 *
 * Notice that this is the only delete method that does not call genericDelete()
 * this is so by design! genericDelete() also deletes theme references and since
 * themes don't have theme references this is unnescessary.
 */
bool Collection::deleteTheme(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	return tc->deleteTheme(id);
}

/**
 * @brief Updates theme.
 *
 * @param t Theme to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the theme
 * except the id to match the object.
 */
bool Collection::updateTheme(Theme t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	tc->updateTheme(t);

	return true;
}

/**
* @brief Updates the themes references to match that of \a b.
*
* @param b Element whose theme references need to be updated.
*/
void Collection::updateThemeReference(Book b)
{
	deleteReference("book", b.getId(), "theme", db);
	insertReferenceBook(b, "theme", db);
}

/**
 * @brief Updates the themes references to match that of \a a.
 *
 * @param a Element whose theme references need to be updated.
 */
void Collection::updateThemeReference(Author a)
{
	deleteReference("author", a.getId(), "theme", db);
	insertReferenceAuthor(a, db);
}

/**
 * @brief Updates the themes references to match that of \a p.
 *
 * @param p Element whose theme references need to be updated.
 */
void Collection::updateThemeReference(Publisher p)
{
	deleteReference("publisher", p.getId(), "theme", db);
	insertReferencePublisher(p, db);
}

template <class t>
void Collection::updateAuthorReference(t data, string type)
{
	deleteReference(type, data.getId(), "author", db);
	insertReferenceBook(data, "author", db);
}

template <class t>
void Collection::updatePublisherReference(t data, string type)
{
	deleteReference(type, data.getId(), "publisher", db);
	insertReferenceBook(data, "publisher", db);
}
