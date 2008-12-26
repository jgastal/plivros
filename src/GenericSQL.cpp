/**
 * @file GenericSQL.cpp
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#include <QtCore/QList>

#include "GenericSQL.h"

/**
 * @brief Adds entries in a table that represent a n:n relationship.
 *
 * @param type Type of element which is referencing others.
 * @param data Element which is referencing others.
 * @param refType Type of element being referenced.
 * @param db Database in which to perform operation.
 *
 * @warning If \a refType is not one of: "theme", "author", "publisher" or \a type
 * is not one of: "book", "publisher", "author" behavior is UNDEFINED. Obviously
 * if the type of \a data is not \a type behavior is also UNDEFINED. DON'T DO THIS!
 *
 * @warning HAS NOT BEEN PROPERLY TESTED! MAY BLOW UP YOUR COMPUTER!
 */
template <class Type, class Reference>
void insertReference(string type, Type data, string refType, DataBase *db) throw(DataBaseException)
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

	PreparedStatement insTemplate("INSERT INTO %1%2 (%3ID, %4ID)"
		" VALUES ('%5', '%6')", db->getType());
	//table name is type+refType(i.e. booktheme, bookauthor, ...)
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
unsigned int genericDelete(unsigned int id, string type, DataBase *db) throw(DataBaseException)
{
	PreparedStatement del("DELETE FROM %1s WHERE id = '%2'", db->getType());
	del.arg(type);
	del.arg(id);

	if(type != "theme")
	{
		PreparedStatement delThemes("DELETE FROM %1theme WHERE %2ID = '%3'", db->getType());

		delThemes.arg(type);
		delThemes.arg(type);
		delThemes.arg(id);

		db->exec(delThemes);
	}

	return db->exec(del);
}
