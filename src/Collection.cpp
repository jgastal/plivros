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
 * The function creates a SQL insert statement based on the given book, executes
 * the statement then sets the id given by the database in the book and returns
 * success.
 */
bool Collection::insertBook(Book &b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->insertBook(b);

	return true;
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Note that this method actually does very little, it just calls genericDelete()
 * with the appropriate arguments.
 */
bool Collection::deleteBook(unsigned int id) throw(DataBaseException)
{
	return bc->deleteBook(id);
}

/**
 * @brief Updates book.
 *
 * @param b Book to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the book
 * except the id to match the object.
 */
bool Collection::updateBook(Book b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->updateBook(b);

	return true;
}

QList<Book> Collection::searchBooks(book_field field, string name) throw(DataBaseException)
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
 * The function creates a SQL insert statement based on the given author, executes
 * the statement then sets the id given by the database in the author and returns
 * success.
 */
bool Collection::insertAuthor(Author &a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->insertAuthor(a);

	return true;
}

/**
 * @brief Deletes author from collection.
 *
 * @param id ID of author to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Note that this method actually does very little, it just calls genericDelete()
 * with the appropriate arguments.
 */
bool Collection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	return ac->deleteAuthor(id);
}

/**
 * @brief Updates author.
 *
 * @param a Book to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the author
 * except the id to match the object.
 */
bool Collection::updateAuthor(Author a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->updateAuthor(a);

	return true;
}

/**
 * @brief Adds publisher \a p to the collection.
 *
 * @param p Publisher to be added.
 *
 * @return Whether the operation was successful.
 *
 * This method creates two SQL commands, one to add the actual publisher and the
 * other one to add the themes associated with it, since internally they are kept
 * in separate tables. After the publisher is inserted in the database its ID is
 * set.
 */
bool Collection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->insertPublisher(p);

	return true;
}

/**
 * @brief Removes publisher from collection.
 *
 * @param id ID of publisher to be removed.
 *
 * @return Whether operation was successful.
 *
 * This method actually does very little, it just calls generic delete which does
 * all the heavy lifting.
 */
bool Collection::deletePublisher(unsigned int id) throw(DataBaseException)
{
	return pc->deletePublisher(id);
}

/**
 * @brief Updates publisher.
 *
 * @param p Publisher to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the publisher
 * except the id to match the object.
 */
bool Collection::updatePublisher(Publisher p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->updatePublisher(p);

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
	PreparedStatement prepStmt("INSERT INTO themes (name, description) "
		"VALUES ('%1', '%2')", db->getType());
	prepStmt.arg(t.getName());
	prepStmt.arg(t.getDescription());

	t.setId(db->insert(prepStmt));

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
	PreparedStatement prepStmt("DELETE FROM themes WHERE id = '%1'", db->getType());
	prepStmt.arg(id);

	db->exec(prepStmt);

	return true;
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
	PreparedStatement prepStmt("UPDATE Themes SET name = '%1', description"
		" = '%2' WHERE id = '%3'", db->getType());
	prepStmt.arg(t.getName());
	prepStmt.arg(t.getDescription());
	prepStmt.arg(t.getId());

	if(db->exec(prepStmt) == 0)
		return false;
	return true;
}

/**
 * @brief Updates the themes references to match that of \a data.
 *
 * @param type Type of object being handled.
 * @param data Object whose theme references need to be updated.
 *
 * @warning type MUST be one of "book", "author", "publisher"!
 * @warning data must be a Book, Author or Publisher object!
 */
template <class T>
void Collection::updateThemesReference(string type, T data) throw(DataBaseException)
{
	PreparedStatement delThemes("DELETE FROM %1themes WHERE %2ID = '%3'", db->getType());
	delThemes.arg(type); //set table name
	delThemes.arg(type); //set id field name
	delThemes.arg(data.getId());

	db->exec(delThemes);

	insertThemesReference(type, data);
}

/**
 * @brief Creates theme references to match that of \a data.
 *
 * @param type Type of object being handled.
 * @param data Object whose theme references need to be added.
 *
 * @warning type MUST be one of "book", "author", "publisher"!
 * @warning data must be a Book, Author or Publisher object!
 */
template <class T>
void Collection::insertThemesReference(string type, T data) throw(DataBaseException)
{
	QList<Theme*> themes = data.getThemes();
	PreparedStatement insThemeTemplate("INSERT INTO %1themes (%2ID, themeID)"
		" VALUES ('%3', '%4')", db->getType());
	insThemeTemplate.arg(type); //set table name
	insThemeTemplate.arg(type); //set id field name
	insThemeTemplate.arg(data.getId()); //id never changes
	for(QList<Theme*>::iterator it = themes.begin(); it != themes.end(); it++)
	{
		PreparedStatement insTheme = insThemeTemplate;
		insTheme.arg((*it)->getId());
		db->insert(insTheme);
	}
}

void Collection::insertAuthorsReference(Book b) throw(DataBaseException)
{
	QList<Author*> authors = b.getAuthors();
	PreparedStatement insAuthorTemplate("INSERT INTO bookauthor (bookID, authorID)"
		" VALUES ('%1', '%2')", db->getType());
	insAuthorTemplate.arg(b.getId());
	for(QList<Author*>::iterator it = authors.begin(); it != authors.end(); it++)
	{
		PreparedStatement insAuthor = insAuthorTemplate;
		insAuthor.arg((*it)->getId());
		db->insert(insAuthor);
	}
}

void Collection::insertPublishersReference(Book b) throw(DataBaseException)
{
	QList<Publisher*> pubs = b.getPublishers();
	PreparedStatement insPubTemplate("INSERT INTO bookpublisher (bookID, publisherID)"
		" VALUES ('%1', '%2')", db->getType());
	insPubTemplate.arg(b.getId());
	for(QList<Publisher*>::iterator it = pubs.begin(); it != pubs.end(); it++)
	{
		PreparedStatement insPub = insPubTemplate;
		insPub.arg((*it)->getId());
		db->insert(insPub);
	}
}

template <class Type, class Reference>
void Collection::insertReference(string type, Type data, string refType) throw(DataBaseException)
{
	QList<Reference*> ref;
	/*
	 * Because of the use of templates ::iterator can be understood as a
	 * nested class or a public name, thus requiring typename to make sure
	 * the parser knows it is a nested class and is being used as a type.
	 * For a full explanation see:
	 * http://pages.cs.wisc.edu/~driscoll/typename.html
	 */
	typename QList<Reference*>::iterator it;
	if(refType == "theme")
		ref = data.getThemes();
	else if(refType == "author")
		ref = data.getAuthors();
	else if(refType == "publisher")
		ref = data.getPublihsers();

	PreparedStatement insTemplate("INSERT INTO %1s%2s (%3ID, %4ID)"
		" VALUES ('%5', '%6')", db->getType());
	//table name is type+refType(i.e. booksthemes, booksauthors, ...)
	insTemplate.arg(type);
	insTemplate.arg(refType);
	//first id is of type
	insTemplate.arg(type);
	//second id is of referenced type
	insTemplate.arg(refType);
	//id of type never changes
	insTemplate.arg(data.getId());
	for(it = ref.begin(); it != ref.end(); it++)
	{
		PreparedStatement ins = insTemplate;
		ins.arg((*it)->getId());
		db->insert(ins);
	}
}

/**
 * @brief Remove an object from the collection.
 *
 * @param id ID of object to removed from collection.
 * @param type Type of object to be removed from collection.
 *
 * @return Whether operation was successful.
 *
 * @warning type MUST be one of "book", "author", "publisher"!
 * @warning Under no circumstance use this method to delete a theme.
 *
 * This method first removes any theme references to the object being removed to
 * only then remove the actual object. The order in which this is done is
 * important to preserve data consistency in the database.
 */
bool Collection::genericDelete(unsigned int id, string type) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement del("DELETE FROM %1s WHERE id = '%2'", db->getType());
	PreparedStatement delThemes("DELETE FROM %1themes WHERE %2ID = '%3'", db->getType());
	del.arg(type);
	del.arg(id);

	delThemes.arg(type);
	delThemes.arg(type);
	delThemes.arg(id);

	db->exec(delThemes);
	db->exec(del);

	return true;
}
