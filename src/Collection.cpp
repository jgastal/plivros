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

#include "Collection.h"
#include "PreparedStatement.h"

using namespace std;

/**
 * @brief Stub constructor calls real constructor with read/write argument.
 */
Collection::Collection(QString u, QString customDbName) throw(bad_alloc)
{
	Collection(u, false, customDbName);
}

/**
 * @brief Opens the database file associated with this collection. Creating a new
 * one if none existed.
 *
 * @param u The name of the user to whom this collection belongs.
 * @param ro If the database should be opened read only.
 * @param customDbName Name to be used for the database file, if empty user name
 * will be used.
 */
Collection::Collection(QString u, bool ro, QString customDbName) throw(bad_alloc)
{
	readOnly = ro;
	user = u;
	if(customDbName.compare("") == 0) //this obviously means empty names are not valid
		dbName = u.append(".db");
	else
		dbName = customDbName;

	db = new DataBase(dbName.toStdString());
}

Collection::~Collection() throw()
{
	delete db;
}

/**
 * @brief Add the book \a b to the collection.
 *
 * @param b Book to be added.
 *
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warn If the collection was opened as read only does nothing and returns false.
 *
 * The function creates a SQL insert statement based on the given book, executes
 * the statement then sets the id given by the database in the book and returns
 * success.
 */
bool Collection::insertBook(Book &b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement prep_stmt("INSERT INTO books (isbn, title, edition, "
		"critique, description, rating, cover, ebook, publishingyear, "
		"udc, translator) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', "
		"'%7', '%8', '%9', '%10', '%11');");
	prep_stmt.arg(b.getIsbn());
	prep_stmt.arg(b.getTitle());
	prep_stmt.arg(b.getEdition());
	prep_stmt.arg(b.getCritique());
	prep_stmt.arg(b.getDescription());
	prep_stmt.arg(b.getRating());
	prep_stmt.arg(b.getCover());
	prep_stmt.arg(b.getEbook());
	prep_stmt.arg(b.getPubDate().toString("yyyy-MM-dd").toStdString());
	prep_stmt.arg(b.getUDC());
	prep_stmt.arg(b.getTranslator()->getId());

	b.setId(db->insert(prep_stmt));

	insertThemesReference("book", b);

	return true;
}

bool Collection::deleteBook(unsigned int id) throw(DataBaseException)
{
	return genericDelete(id, "book");
}

bool Collection::updateBook(unsigned int id, Book b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement upd_book("UPDATE books SET isbn = '%1', title = '%2',"
		" edition = '%3', description = '%4', critique = '%5', rating ="
		" '%6', cover = '%7', ebook = '%8', publishingyear = '%9', udc ="
		" '%10', translator = '%11' WHERE id = '%12'");
	upd_book.arg(b.getIsbn());
	upd_book.arg(b.getTitle());
	upd_book.arg(b.getEdition());
	upd_book.arg(b.getDescription());
	upd_book.arg(b.getCritique());
	upd_book.arg(b.getRating());
	upd_book.arg(b.getCover());
	upd_book.arg(b.getEbook());
	upd_book.arg(b.getPubDate().toString("yyyy-MM-dd").toStdString());
	upd_book.arg(b.getUDC());
	upd_book.arg(b.getTranslator()->getId());
	upd_book.arg(id);

	updateThemesReference("book", b);

	if(db->exec(upd_book) == 0)
		return false;
	return true;
}

bool Collection::insertAuthor(Author &a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement ins_author("INSERT INTO authors (firstname, lastname, "
		"description, critique, rating, picture) VALUES ('%1', '%2', "
		"'%3', '%4', '%5', '%6');");
	ins_author.arg(a.getFirstName());
	ins_author.arg(a.getLastName());
	ins_author.arg(a.getDescription());
	ins_author.arg(a.getCritique());
	ins_author.arg(a.getRating());
	ins_author.arg(a.getPicture());

	a.setId(db->insert(ins_author));

	insertThemesReference("author", a);

	return true;
}

bool Collection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	return genericDelete(id, "author");
}

bool Collection::updateAuthor(unsigned int id, Author a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement upd_author("UPDATE authors SET firstname = '%1', "
		"lastname = '%2', description = '%3', critique = '%4', rating = "
		"'%5', picture = '%6' WHERE id = '%7'");
	upd_author.arg(a.getFirstName());
	upd_author.arg(a.getLastName());
	upd_author.arg(a.getDescription());
	upd_author.arg(a.getCritique());
	upd_author.arg(a.getRating());
	upd_author.arg(a.getPicture());

	updateThemesReference("author", a);

	if(db->exec(upd_author) == 0)
		return false;
	return true;
}

bool Collection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement ins_pub("INSERT INTO publishers (name, description, critique,"
		"logo) VALUES ('%1', '%2', '%3', '%4');");
	ins_pub.arg(p.getName());
	ins_pub.arg(p.getDescription());
	ins_pub.arg(p.getCritique());
	ins_pub.arg(p.getLogo());

	p.setId(db->insert(ins_pub));

	insertThemesReference("publisher", p);

	return true;
}

bool Collection::deletePublisher(unsigned int id) throw(DataBaseException)
{
	return genericDelete(id, "publisher");
}

bool Collection::updatePublisher(unsigned int id, Publisher p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement upd_pub("UPDATE publishers SET name = '%1', description = '%2', critique = '%3', logo = '%4' WHERE id = '%5'");
	upd_pub.arg(p.getName());
	upd_pub.arg(p.getDescription());
	upd_pub.arg(p.getCritique());
	upd_pub.arg(p.getLogo());

	updateThemesReference("publisher", p);

	if(db->exec(upd_pub) == 0)
		return false;
	return true;
}

/**
 * @brief Adds the theme \a t to the collection.
 *
 * @param t The theme to be inserted.
 *
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warn If the collection was opened as read only does nothing and returns false.
 *
 * The function creates a SQL insert statement based on the given theme, executes
 * the statement then sets the id given by the database in the theme and returns
 * success.
 */
bool Collection::insertTheme(Theme &t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement prep_stmt("INSERT INTO themes (name, description) VALUES ('%1', '%2');");
	prep_stmt.arg(t.getName());
	prep_stmt.arg(t.getDescription());

	t.setId(db->insert(prep_stmt));

	return true;
}

bool Collection::deleteTheme(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement prep_stmt("DELETE FROM themes WHERE id = '%1';");
	prep_stmt.arg(id);

	db->exec(prep_stmt);

	return true;
}

bool Collection::updateTheme(unsigned int id, Theme t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	PreparedStatement prep_stmt("UPDATE Themes SET name = '%1', description = '%2' WHERE id = '%3';");
	prep_stmt.arg(t.getName());
	prep_stmt.arg(t.getDescription());
	prep_stmt.arg(id);

	if(db->exec(prep_stmt) == 0)
		return false;
	return true;
}

template <class T>
void Collection::updateThemesReference(string type, T data)
{
	PreparedStatement del_themes("DELETE FROM %1themes WHERE %2ID = '%3'");
	del_themes.arg(type); //set table name
	del_themes.arg(type); //set id field name
	del_themes.arg(data.getId());

	db->exec(del_themes);

	insertThemesReference(type, data);
}

template <class T>
void Collection::insertThemesReference(string type, T data)
{
	QList<Theme*> themes = data.getThemes();
	PreparedStatement ins_theme_template("INSERT INTO %1themes (%2ID, themeID) VALUES ('%3', '%4');");
	ins_theme_template.arg(type); //set table name
	ins_theme_template.arg(type); //set id field name
	for(QList<Theme*>::iterator it = themes.begin(); it != themes.end(); it++)
	{
		PreparedStatement ins_theme = ins_theme_template;
		ins_theme.arg(data.getId());
		ins_theme.arg((*it)->getId());
		db->insert(ins_theme);
	}
}

bool Collection::genericDelete(unsigned int id, string type)
{
	if(readOnly)
		return false;
	PreparedStatement del("DELETE FROM %1s WHERE id = '%2'");
	PreparedStatement del_themes("DELETE FROM %1themes WHERE %2ID = '%3'");
	del.arg(type);
	del.arg(id);

	del_themes.arg(type);
	del_themes.arg(type);
	del_themes.arg(id);

	db->exec(del_themes);
	db->exec(del);

	return true;
}
