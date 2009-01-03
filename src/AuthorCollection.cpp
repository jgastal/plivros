/**
 * @file AuthorsCollection.cpp
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#include "AuthorCollection.h"

#include "DataBase.h"
#include "DataBaseException.h"
#include "PreparedStatement.h"

#include "Author.h"
#include "Theme.h"
#include "GenericSQL.h"

AuthorsCollection::AuthorsCollection(DataBase *db)
{
	this->db = db;
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
bool AuthorsCollection::insertAuthor(Author &a) throw(DataBaseException)
{
	PreparedStatement insAuthor("INSERT INTO authors (firstname, lastname, "
		"description, critique, rating, picture) VALUES ('%1', '%2', "
		"'%3', '%4', '%5', '%6')", db->getType());
	insAuthor.arg(a.getFirstName());
	insAuthor.arg(a.getLastName());
	insAuthor.arg(a.getDescription());
	insAuthor.arg(a.getCritique());
	insAuthor.arg(a.getRating());
	insAuthor.arg(a.getPicture());

	a.setId(db->insert(insAuthor));

	insertThemesReference("author", a);

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
bool AuthorsCollection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	genericDelete(id, "author", db);
	return true;
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
bool AuthorsCollection::updateAuthor(Author a) throw(DataBaseException)
{
	PreparedStatement updAuthor("UPDATE authors SET firstname = '%1', "
		"lastname = '%2', description = '%3', critique = '%4', rating = "
		"'%5', picture = '%6' WHERE id = '%7'", db->getType());
	updAuthor.arg(a.getFirstName());
	updAuthor.arg(a.getDescription());
	updAuthor.arg(a.getCritique());
	updAuthor.arg(a.getRating());
	updAuthor.arg(a.getPicture());

	updateThemesReference("author", a);

	if(db->exec(updAuthor) == 0)
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
void AuthorsCollection::updateThemesReference(string type, T data) throw(DataBaseException)
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
void AuthorsCollection::insertThemesReference(string type, T data) throw(DataBaseException)
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
