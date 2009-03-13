/**
 * @file BookCollection.cpp
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#include "BookCollection.h"

#include "DataBase.h"
#include "ResultSet.h"
#include "PreparedStatement.h"
#include "DataBaseException.h"

#include "GenericSQL.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

/**
 * @brief Initializes member variables.
 *
 * @param db Database in which operations will be executed.
 */
BookCollection::BookCollection(DataBase *db) throw()
{
	this->db = db;
}

/**
 * @brief Add book \a b to the collection.
 *
 * @param b Book to be added.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warning Make sure you DON'T SET the books id before calling this method.
 *
 * Adds \a b to the DataBase and sets its id. Nothing is done with the referenced
 * authors, publishers and themes.
 */
void BookCollection::insertBook(Book &b) throw(DataBaseException)
{
	PreparedStatement prepStmt("INSERT INTO books (isbn, title, edition, "
		"critique, description, rating, cover, ebook, publishingyear, "
		"udc, translator) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', "
		"'%7', '%8', '%9', '%10', '%11')", db->getType());
	prepStmt.arg(b.getIsbn());
	prepStmt.arg(b.getTitle());
	prepStmt.arg(b.getEdition());
	prepStmt.arg(b.getCritique());
	prepStmt.arg(b.getDescription());
	prepStmt.arg(b.getRating());
	prepStmt.arg(b.getCover());
	prepStmt.arg(b.getEbook());
	prepStmt.arg(b.getPubDate().toString("yyyy-MM-dd").toStdString());
	prepStmt.arg(b.getUDC());
	prepStmt.arg(b.getTranslator().getId());

	b.setId(db->insert(prepStmt));
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful. May fail if no book has this \a id.
 *
 * Deletes the book with no regard to possible references to it.
 */
bool BookCollection::deleteBook(unsigned int id) throw(DataBaseException)
{
	if(genericDelete(id, "book", db) == 1)
		return true;
	return false;
}

/**
 * @brief Updates book.
 *
 * @param b Book to be updated.
 *
 * This method updates every field of the book, except the id and the referenced
 * authors, publishers and themes.
 */
void BookCollection::updateBook(Book b) throw(DataBaseException)
{
	PreparedStatement updBook("UPDATE books SET isbn = '%1', title = '%2',"
		" edition = '%3', description = '%4', critique = '%5', rating ="
		" '%6', cover = '%7', ebook = '%8', publishingyear = '%9', udc ="
		" '%10', translator = '%11' WHERE id = '%12'", db->getType());
	updBook.arg(b.getIsbn());
	updBook.arg(b.getTitle());
	updBook.arg(b.getEdition());
	updBook.arg(b.getDescription());
	updBook.arg(b.getCritique());
	updBook.arg(b.getRating());
	updBook.arg(b.getCover());
	updBook.arg(b.getEbook());
	updBook.arg(b.getPubDate().toString("yyyy-MM-dd").toStdString());
	updBook.arg(b.getUDC());
	updBook.arg(b.getTranslator().getId());
	updBook.arg(b.getId());

	db->exec(updBook);
}