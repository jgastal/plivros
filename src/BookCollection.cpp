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
BookCollection::BookCollection(DataBase *db)
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
 * The function creates a SQL insert statement based on the given book, executes
 * the statement then sets the id given by the database in the book.
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
	if(b.getTranslator())
		prepStmt.arg(b.getTranslator()->getId());
	else
		prepStmt.arg(-1);

	b.setId(db->insert(prepStmt));

	insertThemesReference(b);
	insertAuthorsReference(b);
	insertPublishersReference(b);
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful. May fail if the no book has this \a
 * id.
 *
 * Note that this method actually does very little, it just calls genericDelete()
 * with the appropriate arguments.
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
 * This method updates every field of the book, except the id, to match \a b.
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
	updBook.arg(b.getTranslator()->getId());
	updBook.arg(b.getId());

	updateThemesReference(b);
	updateAuthorsReference(b);
	updatePublishersReference(b);

	db->exec(updBook);
}

/**
 * @brief Search for books.
 *
 * @param field What field of the book you would like to search for.
 * @param name Value which should be searched for.
 *
 * @return List of books matching the criteria.
 *
 * This search returns all books that match the search criteria. The search
 * is not done by exact match but rather by checking if the field contains the
 * value, that means that searching for "ball" in title will include titles such
 * as "goofball".
 * If the search is done in authors it will be considered a match if either the
 * first or last name of the author matches the searched value. In searches be
 * publisher and theme it will be considered a match if the name matches the
 * searched value.
 */
QList<Book> BookCollection::searchBooks(book_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("SELECT * FROM books WHERE %1 %2 (%3)", db->getType());
	if(field == b_authors)
	{
		query.arg("id"); //search for book id
		query.arg("IN"); //using subquery
		string refQuery("SELECT bookID FROM bookauthors WHERE authorID IN (%1)");
		string authorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' || lastname LIKE '%%2%')");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from authors table
		query.arg(name); //search in first name
		query.arg(name); //search in last name
	}
	else if(field == b_publishers)
	{
		query.arg("id"); //search for book id
		query.arg("IN"); //using subquery
		string refQuery("SELECT bookID FROM bookpublishers WHERE publisherID IN (%1)");
		string authorQuery("SELECT id FROM publishers WHERE name LIKE '%%1%'");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from publishers table
		query.arg(name); //search in name
	}
	else if(field == b_themes)
	{
		query.arg("id"); //search for book id
		query.arg("IN"); //using subquery
		string refQuery("SELECT bookID FROM bookthemes WHERE themeID IN (%1)");
		string authorQuery("SELECT id FROM themes WHERE name LIKE '%%1%'");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from themes table
		query.arg(name); //search in name
	}
	else if(field == b_translator)
	{
		query.arg("translator");
		query.arg("IN");
		string translatorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' || lastname LIKE '%%2%')");
		query.arg(translatorQuery);
		query.arg(name);
	}
	else
	{
		//what field to search for
		if(field == b_isbn)
			query.arg("isbn");
		else if(field == b_title)
			query.arg("title");
		else if(field == b_edition)
			query.arg("edition");
		else if(field == b_critique)
			query.arg("critique");
		else if(field == b_description)
			query.arg("description");
		else if(field == b_rating)
			query.arg("rating");
		else if(field == b_cover)
			query.arg("cover");
		else if(field == b_ebook)
			query.arg("ebook");
		else if(field == b_pubdate)
			query.arg("pubdate");
		else if(field == b_UDC)
			query.arg("UDC");

		query.arg("LIKE"); //doesn't have to be exact match
		name.insert(0, "'%").append("%'"); //SQLs LIKE requires a preceding '%' and a ending '%'
		query.arg(name); //search term
	}

	ResultSet bookRS = db->query(query);
	return parseBookResultSet(bookRS);
}

/**
 * @brief Creates theme references to match that of \a b.
 *
 * @param b Books whose themes need to be referenced.
 */
void BookCollection::insertThemesReference(Book b) throw(DataBaseException)
{
	insertReferenceBook(b, "theme", db);
}

/**
 * @brief Creates author references to match that of \a b.
 *
 * @param b Books whose authors need to be referenced.
 */
void BookCollection::insertAuthorsReference(Book b) throw(DataBaseException)
{
	insertReferenceBook(b, "author", db);
}

/**
 * @brief Creates publisher references to match that of \a b.
 *
 * @param b Books whose publishers need to be referenced.
 */
void BookCollection::insertPublishersReference(Book b) throw(DataBaseException)
{
	insertReferenceBook(b, "publisher", db);
}

/**
 * @brief Updates the themes references to match that of \a b.
 *
 * @param b Book whose theme references need to be updated.
 */
void BookCollection::updateThemesReference(Book b) throw(DataBaseException)
{
	deleteReference("book", b.getId(), "theme", db);
	insertThemesReference(b);
}

/**
 * @brief Updates the author references to match that of \a b.
 *
 * @param b Book whose authors references need to be updated.
 */
void BookCollection::updateAuthorsReference(Book b) throw(DataBaseException)
{
	deleteReference("book", b.getId(), "author", db);
	insertAuthorsReference(b);
	return;
}

/**
 * @brief Updates the publisher references to match that of \a b.
 *
 * @param b Book whose publishers references need to be updated.
 */
void BookCollection::updatePublishersReference(Book b) throw(DataBaseException)
{
	deleteReference("book", b.getId(), "publisher", db);
	insertPublishersReference(b);
	return;
}

QList<Book> BookCollection::parseBookResultSet(ResultSet rs)
{
	bookList.clear();
	while(rs.nextRow())
	{
		//TODO implement
	}
	return bookList;
}
