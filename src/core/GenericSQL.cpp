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
 * @file GenericSQL.cpp
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#include <QtCore/QList>

#include "DataBase.h"
#include "PreparedStatement.h"

#include "GenericSQL.h"

#include "Book.h"
#include "Theme.h"
#include "Author.h"
#include "Publisher.h"

//These prototypes are here because this functions shouldn't be used outside this file.
PreparedStatement buildInsTemplate(QString type, DataObject *data, QString refType, DataBase *db) throw(DataBaseException);
template <class Type>
void insertReferenceLoop(QList<Type> ref, PreparedStatement tpl, DataBase *db) throw(DataBaseException);

/**
 * @brief Insert entries in a table that represent a n:n relationship between book
 * and \a refType.
 *
 * @param b Books whose references need to be inserted.
 * @param refType Type of obejct whose reference will be included. Valid values
 * are: "theme", "author", "publisher".
 * @param db DataBase in which operation will be executed.
 */
void insertReference(Book &b, QString refType, DataBase *db) throw(DataBaseException)
{
	PreparedStatement insTpl = buildInsTemplate("book", &b, refType, db);
	if(refType == "theme")
		insertReferenceLoop(b.getThemes(), insTpl, db);
	else if(refType == "author")
		insertReferenceLoop(b.getAuthors(), insTpl, db);
	else if(refType == "publisher")
		insertReferenceLoop(b.getPublishers(), insTpl, db);
}

/**
 * @brief Insert the theme/author references in the database.
 *
 * @param a Author whose theme references need to be included.
 * @param db DataBase in which to include references.
 */
void insertReference(Author &a, DataBase *db) throw(DataBaseException)
{
	PreparedStatement insTpl = buildInsTemplate("author", &a, "theme", db);
	insertReferenceLoop(a.getThemes(), insTpl, db);
}

/**
 * @brief Insert the theme/publisher references in the database.
 *
 * @param p Publisher whose theme references need to be included.
 * @param db DataBase in which to include references.
 */
void insertReference(Publisher &p, DataBase *db) throw(DataBaseException)
{
	PreparedStatement insTpl = buildInsTemplate("publisher", &p, "theme", db);
	insertReferenceLoop(p.getThemes(), insTpl, db);
}

/**
 * @brief Creates a template of a INSERT command.
 *
 * @param type Type of element which is referencing others.
 * @param data Element which is referencing others.
 * @param refType Type of element being referenced.
 * @param db Database in which to perform operation.
 *
 * Creates a PreparedStatement which is a template of a INSERT command into a
 * table with name: type+refType. This PreparedStatement has to receive the id
 * of the referenced object(probably a theme).
 */
PreparedStatement buildInsTemplate(QString type, DataObject *data, QString refType, DataBase *db) throw(DataBaseException)
{
	PreparedStatement insTemplate("INSERT INTO %1s%2s (%3sid, %4sid)"
		" VALUES ('%5', '%6')", db->getType());
	//table name is type+refType(i.e. booksthemes, booksauthors, ...)
	insTemplate.arg(type.toStdString());
	insTemplate.arg(refType.toStdString());
	//first id is of type
	insTemplate.arg(type.toStdString());
	//second id is of referenced type
	insTemplate.arg(refType.toStdString());
	//id of type never changes
	insTemplate.arg(data->getId());

	return insTemplate;
}

/**
 * @brief Iterates through \a ref substituting elements id in \a tpl and executing it.
 *
 * @param ref List of pointer to objects to be iterated through.
 * @param tpl Template of SQL command.
 * @param db DataBase in which the command should be executed.
 *
 * Iterates though the \a ref list and for each element substitutes its id in the
 * \a tpl PreparedStatement, after substitution \a tpl is executed. Note that
 * only one substitution will be done in \a tpl.
 */
template <class Type>
void insertReferenceLoop(QList<Type> ref, PreparedStatement tpl, DataBase *db) throw(DataBaseException)
{
	/*
	 * Because of the use of templates ::iterator can be understood as a
	 * nested class or a public member name, thus requiring typename to make
	 * sure the parser knows it is a nested class and is being used as a type.
	 * For a full explanation see:
	 * http://pages.cs.wisc.edu/~driscoll/typename.html
	 */
	typename QList<Type>::iterator it;
	for(it = ref.begin(); it != ref.end(); it++)
	{
		PreparedStatement sql = tpl;
		sql.arg((*it).getId());
		db->exec(sql);
	}
}

/**
 * @brief Removes all references of \a refType referenced by object with id \a id.
 *
 * @param type Type of element that referenced. Must be one of: "book", "author",
 * "publisher".
 * @param id ID of element that referenced.
 * @param refType Type of element being referenced. Must be one of: "author",
 * "publisher", "theme".
 * @param db DataBase in which to execute operation.
 */
void deleteReference(QString type, unsigned int id, QString refType, DataBase *db) throw(DataBaseException)
{
	PreparedStatement del("DELETE FROM %1s%2s WHERE %3sid = '%4'", db->getType());

	//Table has name type+refType (e.g. booksthemes, booksauthors, ...).
	del.arg(type.toStdString());
	del.arg(refType.toStdString());

	/*
	 * Delete all that was referenced by element with typesID = id.
	 * For example "DELETE FROM bookauthor WHERE booksID = '123'"
	 */
	del.arg(type.toStdString());
	del.arg(id);

	db->exec(del);
}

/**
 * @brief Remove an object from the collection.
 *
 * @param id ID of object to removed from collection.
 * @param type Type of object to be removed from collection.
 * @param db Database from which to delete this object.
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
unsigned int genericDelete(unsigned int id, QString type, DataBase *db) throw(DataBaseException)
{
	PreparedStatement del("DELETE FROM %1s WHERE id = '%2'", db->getType());
	del.arg(type.toStdString());
	del.arg(id);

	return db->exec(del);
}
