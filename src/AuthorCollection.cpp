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
#include "GenericSQL.h"

AuthorCollection::AuthorCollection(DataBase *db)
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
void AuthorCollection::insertAuthor(Author &a) throw(DataBaseException)
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

	insertThemesReference(a);
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
bool AuthorCollection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	if(genericDelete(id, "author", db) == 1)
		return true;
	return false;
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
void AuthorCollection::updateAuthor(Author a) throw(DataBaseException)
{
	PreparedStatement updAuthor("UPDATE authors SET firstname = '%1', "
		"lastname = '%2', description = '%3', critique = '%4', rating = "
		"'%5', picture = '%6' WHERE id = '%7'", db->getType());
	updAuthor.arg(a.getFirstName());
	updAuthor.arg(a.getDescription());
	updAuthor.arg(a.getCritique());
	updAuthor.arg(a.getRating());
	updAuthor.arg(a.getPicture());

	updateThemesReference(a);

	db->exec(updAuthor);
}

/**
 * @brief Updates the themes references to match that of \a a.
 *
 * @param a Author whose theme references need to be updated.
 */
void AuthorCollection::updateThemesReference(Author a) throw(DataBaseException)
{
	deleteReference("author", a.getId(), "theme", db);
	insertThemesReference(a);
}

/**
 * @brief Creates theme references to match that of \a a.
 *
 * @param a Author whose themes need to be referenced.
 */
void AuthorCollection::insertThemesReference(Author a) throw(DataBaseException)
{
	insertReferenceAuthor(a, db);
}
