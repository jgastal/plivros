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
 * @file AuthorCollection.cpp
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

AuthorCollection::AuthorCollection(DataBase *db) throw()
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
 * @warning Make sure you DON'T SET the authors id before calling this method.
 *
 * This method adds the author to the collection and sets its id. Nothing is done
 * with the methods referenced by the author.
 */
void AuthorCollection::insertAuthor(Author &a) throw(DataBaseException)
{
	PreparedStatement insAuthor("INSERT INTO authors (firstname, lastname, "
		"description, critique, rating, picture) VALUES ('%1', '%2', "
		"'%3', '%4', '%5', '%6')", db->getType());
	insAuthor.arg(a.getFirstName().toStdString());
	insAuthor.arg(a.getLastName().toStdString());
	insAuthor.arg(a.getDescription().toStdString());
	insAuthor.arg(a.getCritique().toStdString());
	insAuthor.arg(a.getRating());
	insAuthor.arg(a.getPicture().toStdString());

	a.setId(db->insert(insAuthor));
}

/**
 * @brief Deletes author from collection.
 *
 * @param id ID of author to be deleted.
 *
 * @return Whether operation was successful.
 *
 * This method deletes only the author, no checking of references to the author
 * is made.
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
 * All fields except the themes referenced and the id are updated.
 */
void AuthorCollection::updateAuthor(Author a) throw(DataBaseException)
{
	PreparedStatement updAuthor("UPDATE authors SET firstname = '%1', "
		"lastname = '%2', description = '%3', critique = '%4', rating = "
		"'%5', picture = '%6' WHERE id = '%7'", db->getType());
	updAuthor.arg(a.getFirstName().toStdString());
	updAuthor.arg(a.getLastName().toStdString());
	updAuthor.arg(a.getDescription().toStdString());
	updAuthor.arg(a.getCritique().toStdString());
	updAuthor.arg(a.getRating());
	updAuthor.arg(a.getPicture().toStdString());
	updAuthor.arg(a.getId());

	db->exec(updAuthor);
}
