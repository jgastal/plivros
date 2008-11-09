/**
 * @file Collection.cpp
 *
 * @date Nov 4, 2008
 * @author Jonas M. Gastal
 */

#include <QtCore/QString>

#include "DataBase.h"
#include "ResultSet.h"
#include "SQLiteException.h"

#include "Collection.h"
#include "PreparedStatement.h"

using namespace std;

Collection::Collection(QString u, QString customDbName)
{
	Collection(u, false, customDbName);
}

Collection::Collection(QString u, bool ro, QString customDbName)
{
	readOnly = ro;
	user = u;
	if(customDbName.compare("") == 0) //this obviously means empty names are not valid
		dbName = u.append(".db");
	else
		dbName = customDbName;

	db = new DataBase(dbName.toStdString());
}

/**
 * @brief Add the book \a b to the collection.
 *
 * @param b Book to be added.
 *
 * @return Wether the operation was sucessful.
 */
bool Collection::insertBook(Book &b)
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

	return true;
}

bool Collection::insertTheme(Theme &t) throw(bad_alloc,SQLiteException)
{
	if(readOnly)
		return false;
	PreparedStatement prep_stmt("INSERT INTO themes (name, description) VALUES ('%1',' %2');");
	prep_stmt.arg(t.getName());
	prep_stmt.arg(t.getDescription());

	t.setId(db->insert(prep_stmt));

	return true;
}

bool Collection::deleteTheme(unsigned int id) throw(SQLiteException)
{
	PreparedStatement prep_stmt("DELETE FROM themes WHERE id = '%1';");
	prep_stmt.arg(id);

	db->exec(prep_stmt);

	return true;
}

//TODO Define return
Theme Collection::updateTheme(unsigned int id, Theme t) throw(SQLiteException)
{
	PreparedStatement prep_stmt("UPDATE Themes SET name = '%1', description = '%2' WHERE id = '%3';");
	prep_stmt.arg(t.getName());
	prep_stmt.arg(t.getDescription());
	prep_stmt.arg(id);

	db->exec(prep_stmt);
}





