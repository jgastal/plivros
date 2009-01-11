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
QList<Book> BookCollection::searchBooks(Book::book_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("", db->getType());
	if(field == Book::b_authors || field == Book::b_publishers || field == Book::b_themes || field == Book::b_translator)
		query = compositeSearchBooks(field, name);
	else
	{
		query = PreparedStatement("SELECT * FROM books WHERE %1 LIKE %2", db->getType());
		//what field to search for
		if(field == Book::b_isbn)
			query.arg("isbn");
		else if(field == Book::b_title)
			query.arg("title");
		else if(field == Book::b_edition)
			query.arg("edition");
		else if(field == Book::b_critique)
			query.arg("critique");
		else if(field == Book::b_description)
			query.arg("description");
		else if(field == Book::b_rating)
			query.arg("rating");
		else if(field == Book::b_cover)
			query.arg("cover");
		else if(field == Book::b_ebook)
			query.arg("ebook");
		else if(field == Book::b_pubdate)
			query.arg("pubdate");
		else if(field == Book::b_UDC)
			query.arg("UDC");

		name.insert(0, "'%").append("%'"); //SQLs LIKE requires a preceding '%' and a ending '%'
		query.arg(name); //search term
	}

	ResultSet bookRS = db->query(query);
	return parseBookResultSet(bookRS);
}

PreparedStatement BookCollection::compositeSearchBooks(Book::book_field field, string name) throw(DataBaseException)
{
	/*
	 * You should be extremely carefull in changing the order in which the
	 * PreparedStatements are composed. Composing them in the wrong order
	 * may cause characters to be escaped incorrectly.
	 */
	PreparedStatement query("SELECT * FROM books WHERE id IN (%1)", db->getType());
	if(field == Book::b_authors)
	{
		string refQuery("SELECT bookID FROM booksauthors WHERE authorsid IN (%1)");
		string authorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' || lastname LIKE '%%2%')");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from authors table
		query.arg(name); //search in first name
		query.arg(name); //search in last name
	}
	else if(field == Book::b_publishers)
	{
		string refQuery("SELECT bookID FROM bookspublishers WHERE publishersid IN (%1)");
		string authorQuery("SELECT id FROM publishers WHERE name LIKE '%%1%'");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from publishers table
		query.arg(name); //search in name
	}
	else if(field == Book::b_themes)
	{
		string refQuery("SELECT bookID FROM booksthemes WHERE themesid IN (%1)");
		string authorQuery("SELECT id FROM themes WHERE name LIKE '%%1%'");
		query.arg(refQuery); //select from reference table
		query.arg(authorQuery); //select from themes table
		query.arg(name); //search in name
	}
	else if(field == Book::b_translator)
	{
		string translatorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' || lastname LIKE '%%2%')");
		query.arg(translatorQuery);
		query.arg(name);
	}
	return query;
}

QList<Book> BookCollection::parseBookResultSet(ResultSet &rs) throw(DataBaseException)
{
	bookList.clear();
	while(rs.nextRow())
	{
		Book b;
		b.setIsbn(rs.getString("isbn").c_str());
		b.setTitle(rs.getString("title"));
		b.setEdition(rs.getInt("edition"));
		b.setCritique(rs.getString("critique"));
		b.setDescription(rs.getString("description"));
		b.setRating(rs.getInt("rating"));
		b.setCover(rs.getString("cover"));
		b.setEbook(rs.getString("ebook"));
		b.setPubDate(QDate::fromString(rs.getString("date").c_str(), Qt::ISODate));
		b.setUDC(rs.getString("udc"));
		b.setId(rs.getInt("id"));
		b.setAuthors(getBooksAuthors(rs.getInt("id")));
		b.setTranslator(getBooksTranslator(rs.getInt("id")));
		b.setPublishers(getBooksPublishers(rs.getInt("id")));
		b.setThemes(getBooksThemes(rs.getInt("id")));

		bookList.append(b);
	}
	return bookList;
}

QList<Author> BookCollection::getBooksAuthors(int id) throw(DataBaseException)
{
	return QList<Author>();
}

QList<Publisher> BookCollection::getBooksPublishers(int id) throw(DataBaseException)
{
	return QList<Publisher>();
}

QList<Theme> BookCollection::getBooksThemes(int id) throw(DataBaseException)
{
	return QList<Theme>();
}

Author BookCollection::getBooksTranslator(int id) throw(DataBaseException)
{
	return Author();
}
