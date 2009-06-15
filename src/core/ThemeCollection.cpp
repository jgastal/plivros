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
 * @file ThemeCollection.cpp
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#include "ThemeCollection.h"

#include "DataBase.h"
#include "DataBaseException.h"
#include "PreparedStatement.h"

ThemeCollection::ThemeCollection(DataBase *db) throw()
{
	this->db = db;
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
void ThemeCollection::insertTheme(Theme &t) throw(DataBaseException)
{
	PreparedStatement prepStmt("INSERT INTO themes (name, description) "
		"VALUES ('%1', '%2')", db->getType());
	prepStmt.arg(t.getName().toStdString());
	prepStmt.arg(t.getDescription().toStdString());

	t.setId(db->insert(prepStmt));
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
bool ThemeCollection::deleteTheme(unsigned int id) throw(DataBaseException)
{
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
void ThemeCollection::updateTheme(Theme t) throw(DataBaseException)
{
	PreparedStatement prepStmt("UPDATE Themes SET name = '%1', description"
		" = '%2' WHERE id = '%3'", db->getType());
	prepStmt.arg(t.getName().toStdString());
	prepStmt.arg(t.getDescription().toStdString());
	prepStmt.arg(t.getId());

	db->exec(prepStmt);
}
