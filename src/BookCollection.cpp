/**
 * @file BookCollection.cpp
 *
 * @date 26/12/2008
 * @author Jonas M. Gastal
 */

#include "BookCollection.h"

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
 * @return Whether the operation was successful.
 *
 * @exception DataBaseException Forwarding possible database error.
 *
 * @warning If the collection was opened as read only does nothing and returns false.
 * @warning Make sure you DON'T SET the books id before calling this method.
 *
 * The function creates a SQL insert statement based on the given book, executes
 * the statement then sets the id given by the database in the book and returns
 * success.
 */
bool BookCollection::insertBook(Book &b) throw(DataBaseException)
{
	if(readOnly)
		return false;
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
	prepStmt.arg(b.getTranslator()->getId());

	b.setId(db->insert(prepStmt));

	insertThemesReference("book", b);
	insertAuthorsReference(b);
	insertPublishersReference(b);

	return true;
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Note that this method actually does very little, it just calls genericDelete()
 * with the appropriate arguments.
 */
bool BookCollection::deleteBook(unsigned int id) throw(DataBaseException)
{
	return genericDelete(id, "book");
}

/**
 * @brief Updates book.
 *
 * @param b Book to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the book
 * except the id to match the object.
 */
bool BookCollection::updateBook(Book b) throw(DataBaseException)
{
	if(readOnly)
		return false;
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

	updateThemesReference("book", b);
	updateAuthorsReference(b);
	updatePublishersReference(b);

	if(db->exec(updBook) == 0)
		return false;
	return true;
}

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
 * @brief Updates the themes references to match that of \a data.
 *
 * @param type Type of object being handled.
 * @param data Object whose theme references need to be updated.
 *
 * @warning type MUST be one of "book", "author", "publisher"!
 * @warning data must be a Book, Author or Publisher object!
 */
template <class T>
void BookCollection::updateThemesReference(string type, T data) throw(DataBaseException)
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
void BookCollection::insertThemesReference(string type, T data) throw(DataBaseException)
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

void BookCollection::insertAuthorsReference(Book b) throw(DataBaseException)
{
	QList<Author*> authors = b.getAuthors();
	PreparedStatement insAuthorTemplate("INSERT INTO bookauthor (bookID, authorID)"
		" VALUES ('%1', '%2')", db->getType());
	insAuthorTemplate.arg(b.getId());
	for(QList<Author*>::iterator it = authors.begin(); it != authors.end(); it++)
	{
		PreparedStatement insAuthor = insAuthorTemplate;
		insAuthor.arg((*it)->getId());
		db->insert(insAuthor);
	}
}

void BookCollection::insertPublishersReference(Book b) throw(DataBaseException)
{
	QList<Publisher*> pubs = b.getPublishers();
	PreparedStatement insPubTemplate("INSERT INTO bookpublisher (bookID, publisherID)"
		" VALUES ('%1', '%2')", db->getType());
	insPubTemplate.arg(b.getId());
	for(QList<Publisher*>::iterator it = pubs.begin(); it != pubs.end(); it++)
	{
		PreparedStatement insPub = insPubTemplate;
		insPub.arg((*it)->getId());
		db->insert(insPub);
	}
}

