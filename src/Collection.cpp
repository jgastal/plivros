/**
 * @file Collection.cpp
 *
 * @date Nov 4, 2008
 * @author Jonas M. Gastal
 */

#include <QtCore/QString>

#include "DataBase.h"
#include "ResultSet.h"
#include "DataBaseException.h"
#include "PreparedStatement.h"

#include "Collection.h"
#include "BookCollection.h"
#include "AuthorCollection.h"
#include "PublisherCollection.h"
#include "ThemeCollection.h"
#include "GenericSQL.h"

using namespace std;

/**
 * @brief Opens the database associated with this collection. Creating a new
 * one if it didn't exist.
 *
 * @param u The name of the user to whom this collection belongs.
 * @param ro If the database should be opened read only.
 * @param customDbName Name to be used for the database file, if empty user name
 * will be used.
 */
Collection::Collection(QString u, QString customDbName, bool ro) throw(bad_alloc)
{
	readOnly = ro;
	user = u;
	if(customDbName != "") //this obviously means empty names are not valid
		dbName = customDbName;
	else
		dbName = u.append(".db");

	db = new DataBase(dbName.toStdString());
	bc = new BookCollection(db);
	ac = new AuthorCollection(db);
	pc = new PublisherCollection(db);
	tc = new ThemeCollection(db);
}

///@brief Closes database.
Collection::~Collection() throw()
{
	delete db;
	db = 0;
	delete bc;
	bc = 0;
	delete ac;
	ac = 0;
	delete pc;
	pc =  0;
	delete tc;
	tc = 0;
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
 * This methods adds \a b to the database sets its id and insert the references
 * made to authors, publishers and themes.
 */
bool Collection::insertBook(Book &b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->insertBook(b);
	insertReference(b, "theme", db);
	insertReference(b, "author", db);
	insertReference(b, "publisher", db);

	return true;
}

/**
 * @brief Deletes book from collection.
 *
 * @param id ID of book to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Deletes every author, publisher and theme reference to the book and the book
 * itself.
 */
bool Collection::deleteBook(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	deleteReference("book", id, "theme", db);
	deleteReference("book", id, "author", db);
	deleteReference("book", id, "publisher", db);
	return bc->deleteBook(id);
}

/**
 * @brief Updates book.
 *
 * @param b Book to be updated.
 *
 * @return Whether the operation was successful.
 *
 * Update every field of the book except the id but including the referenced
 * author, publishers and authors.
 */
bool Collection::updateBook(Book b) throw(DataBaseException)
{
	if(readOnly)
		return false;
	bc->updateBook(b);
	updateAuthorReference(b, "book");
	updatePublisherReference(b, "book");
	updateThemeReference(b);

	return true;
}

/**
 * @brief Searches for books.
 *
 * @param field What field of the book you would like to search in.
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
QList<Book> Collection::searchBooks(Book::book_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("", db->getType());
	if(field == Book::b_authors || field == Book::b_publishers || field == Book::b_themes || field == Book::b_translator)
		query = compositeSearchBooks(field, name);
	else
	{
		query = PreparedStatement("SELECT * FROM books WHERE %1 LIKE '%2'", db->getType());
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
		
		name.insert(0, "%").append("%"); //SQLs LIKE requires a preceding '%' and a ending '%'
		query.arg(name); //search term
	}
	
	ResultSet bookRS = db->query(query);
	return parseBookResultSet(bookRS);
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
 * This method adds both the author and the theme references it makes to the
 * database. The id of the author is set.
 */
bool Collection::insertAuthor(Author &a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->insertAuthor(a); //inserts author
	insertReference(a, db); //insert author/theme references

	return true;
}

/**
 * @brief Deletes author from collection.
 *
 * @param id ID of author to be deleted.
 *
 * @return Whether operation was successful.
 *
 * Deletes both the referenced themes and the author.
 */
bool Collection::deleteAuthor(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	deleteReference("author", id, "theme", db);
	return ac->deleteAuthor(id);
}

/**
 * @brief Updates author.
 *
 * @param a Author to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method updates all fields of the author except the id bu including the
 * themes references.
 */
bool Collection::updateAuthor(Author a) throw(DataBaseException)
{
	if(readOnly)
		return false;
	ac->updateAuthor(a);
	updateThemeReference(a);

	return true;
}


/**
 * @brief Searches for authors.
 *
 * @param field What field of the author you would like to search in.
 * @param name Value which should be searched for.
 *
 * @return List of books matching the criteria.
 *
 * This search returns all authors that match the search criteria. The search
 * is not done by exact match but rather by checking if the field contains the
 * value, that means that searching for "ball" in name will include authors such
 * as "goofball".
 * If the search is done theme it will be considered a match if the name matches the
 * searched value.
 */
QList<Author> Collection::searchAuthors(Author::author_field field, string name)
{
	PreparedStatement query("", db->getType());
	if(field == Author::a_themes)
		query = compositeSearchAuthors(field, name);
	else
		query = simpleSearchAuthors(field, name);

	ResultSet authorrs = db->query(query);
	return parseAuthorResultSet(authorrs);
}

/**
 * @brief Adds publisher \a p to the collection.
 *
 * @param p Publisher to be added.
 *
 * @return Whether the operation was successful.
 *
 * This method adds the publisher and all associated references to the DataBase
 * and then sets the publishers id.
 */
bool Collection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->insertPublisher(p);
	insertReference(p, db);

	return true;
}

/**
 * @brief Removes publisher from collection.
 *
 * @param id ID of publisher to be removed.
 *
 * @return Whether operation was successful.
 *
 * Deletes any theme references to this publisher and the publisher itself.
 */
bool Collection::deletePublisher(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;

	deleteReference("publisher", id, "theme", db);
	return pc->deletePublisher(id);
}

/**
 * @brief Updates publisher.
 *
 * @param p Publisher to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method update every field of the publisher except the id but including
 * referenced mehtods.
 */
bool Collection::updatePublisher(Publisher p) throw(DataBaseException)
{
	if(readOnly)
		return false;
	pc->updatePublisher(p);
	updateThemeReference(p);

	return true;
}

QList<Publisher> Collection::searchPublishers(Publisher::publisher_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("", db->getType());
	if(field == Publisher::p_themes)
		query = compositeSearchPublishers(field, name);
	else
		query = simpleSearchPublishers(field, name);

	ResultSet pubrs = db->query(query);
	return parsePublisherResultSet(pubrs);
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
 * @warning Make sure you DON'T SET the themes id before calling this method.
 *
 * The function creates a SQL insert statement based on the given theme, executes
 * the statement then sets the id given by the database in the theme and returns
 * success.
 */
bool Collection::insertTheme(Theme &t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	tc->insertTheme(t);

	return true;
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
bool Collection::deleteTheme(unsigned int id) throw(DataBaseException)
{
	if(readOnly)
		return false;
	return tc->deleteTheme(id);
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
bool Collection::updateTheme(Theme t) throw(DataBaseException)
{
	if(readOnly)
		return false;
	tc->updateTheme(t);

	return true;
}

/**
 * @brief Searches for themes.
 *
 * @param field In what field should the search be performed.
 * @param name What should be searched for.
 *
 * Creates a list(QList) of themes that match the given criteria. The search is
 * not by exact match but rather by "contains", meaning if there is a theme whose
 * name is "theme1" and \a field is t_name and \a name is "the" the search result
 * will include said theme.
 */
QList<Theme> Collection::searchThemes(Theme::theme_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("SELECT * FROM themes WHERE %1 LIKE '%%2%'", db->getType());
	if(field == Theme::t_name)
		query.arg("name");
	else if(field == Theme::t_description)
		query.arg("description");

	query.arg(name);

	ResultSet themers = db->query(query);
	return parseThemeResultSet(themers);
}

/**
 * @brief Updates the themes references to match that of \a b.
 *
 * @param b Element whose theme references need to be updated.
 */
void Collection::updateThemeReference(Book b) throw(DataBaseException)
{
	deleteReference("book", b.getId(), "theme", db);
	insertReference(b, "theme", db);
}

/**
 * @brief Updates the themes references to match that of \a a.
 *
 * @param a Element whose theme references need to be updated.
 */
void Collection::updateThemeReference(Author a) throw(DataBaseException)
{
	deleteReference("author", a.getId(), "theme", db);
	insertReference(a, db);
}

/**
 * @brief Updates the themes references to match that of \a p.
 *
 * @param p Element whose theme references need to be updated.
 */
void Collection::updateThemeReference(Publisher p) throw(DataBaseException)
{
	deleteReference("publisher", p.getId(), "theme", db);
	insertReference(p, db);
}

/**
 * @brief Updates the authors references to match that of \a data.
 *
 * @param data Element whose author references need to be updated.
 * @param type The type of element referencing the authors.
 */
template <class t>
void Collection::updateAuthorReference(t data, string type) throw(DataBaseException)
{
	deleteReference(type, data.getId(), "author", db);
	insertReference(data, "author", db);
}

/**
 * @brief Updates the publishers references to match that of \a data.
 *
 * @param data Element whose publishers references need to be updated.
 * @param type The type of element referencing the publishers.
 */
template <class t>
void Collection::updatePublisherReference(t data, string type) throw(DataBaseException)
{
	deleteReference(type, data.getId(), "publisher", db);
	insertReference(data, "publisher", db);
}

/**
 * @brief Creates a PreparedStatement to search for books searching by author,
 * translator, publishers or theme.
 *
 * @param field Where to search: author, translator, publishers or themes.
 * @param name What to search for.
 *
 * @exception DataBaseException In case there is some PreparedStatement error.
 *
 * @return A PreparedStatement that contains a composite select statement.
 *
 * This method creates a PreparedStatement that searches for a given keyword
 * contained in the first or last name of authors or translator, name of publisher
 * or theme. As mentioned the search is not done by exact match but rather by
 * "contains". 
 */
PreparedStatement Collection::compositeSearchBooks(Book::book_field field, string name) throw(DataBaseException)
{
	/*
	 * The composing of the query is first done using QString(and not PreparedStatements) because
	 * otherwise ' in '%1' would be escaped and that is obviously unwanted. There might be a more
	 * elagant solution(one that doesn't depend on QString) but this one works and is readable.
	 */
	QString query("SELECT * FROM books WHERE id IN (%1)");

	if(field == Book::b_authors)
	{
		QString refQuery("SELECT booksid FROM booksauthors WHERE authorsid IN (%1)");
		query = query.arg(refQuery); //select from reference table
		QString authorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' OR lastname LIKE '%%2%')");
		query = query.arg(authorQuery); //select from authors table
	}
	else if(field == Book::b_publishers)
	{
		QString refQuery("SELECT booksid FROM bookspublishers WHERE publishersid IN (%1)");
		query = query.arg(refQuery); //select from reference table
		QString pubQuery("SELECT id FROM publishers WHERE name LIKE '%%1%'");
		query = query.arg(pubQuery); //select from publishers table
	}
	else if(field == Book::b_themes)
	{
		QString refQuery("SELECT booksid FROM booksthemes WHERE themesid IN (%1)");
		query = query.arg(refQuery); //select from reference table
		QString themeQuery("SELECT id FROM themes WHERE name LIKE '%%1%'");
		query = query.arg(themeQuery); //select from themes table
	}
	else if(field == Book::b_translator)
	{
		QString translatorQuery("SELECT id FROM authors WHERE (firstname LIKE '%%1%' OR lastname LIKE '%%2%')");
		query = query.arg(translatorQuery);
	}

	PreparedStatement ret(query.toStdString(), db->getType());
	ret.arg(name);
	ret.arg(name);

	return ret;
}

/**
 * @brief Transform a result set into a QList.
 *
 * @param rs ResultSet to be parsed.
 *
 * @return Returns a QList of books containing all books in the result set(possibly 0).
 *
 * @warning The query that originated \a rs must contain ALL fields in the books
 * table.
 */
QList<Book> Collection::parseBookResultSet(ResultSet &rs) throw(DataBaseException)
{
	QList<Book> bookList;
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
		b.setPubDate(QDate::fromString(rs.getString("publishingyear").c_str(), Qt::ISODate));
		b.setUDC(rs.getString("udc"));
		b.setId(rs.getInt("id"));
		b.setAuthors(getBooksAuthors(rs.getInt("id")));
		b.setTranslator(getBooksTranslator(rs.getInt("translator")));
		b.setPublishers(getBooksPublishers(rs.getInt("id")));
		b.setThemes(getBooksThemes(rs.getInt("id")));

		bookList.append(b);
	}
	return bookList;
}

/**
 * @brief Gets all authors associated with a given book.
 *
 * @param id id of book whose authors are desired.
 *
 * @return QList of authors associated with book.
 */
QList<Author> Collection::getBooksAuthors(int id) throw(DataBaseException)
{
	PreparedStatement authors("SELECT * FROM authors WHERE id IN (%1)", db->getType());
	string authorsbooks("SELECT authorsid FROM booksauthors WHERE booksid = %1");
	authors.arg(authorsbooks);
	authors.arg(id);

	ResultSet rs = db->query(authors);
	return parseAuthorResultSet(rs);
}

/**
 * @brief Gets all publishers associated with a given book.
 *
 * @param id id of book whose publishers are desired.
 *
 * @return QList of publishers associated with book.
 */
QList<Publisher> Collection::getBooksPublishers(int id) throw(DataBaseException)
{
	PreparedStatement publishers("SELECT * FROM publishers WHERE id IN (%1)", db->getType());
	string publishersbooks("SELECT publishersid FROM bookspublishers WHERE booksid = %1");
	publishers.arg(publishersbooks);
	publishers.arg(id);
	
	ResultSet rs = db->query(publishers);
	return parsePublisherResultSet(rs);
}

/**
 * @brief Gets all themes associated with a given book.
 *
 * @param id id of book whose themes are desired.
 *
 * @return QList of themes associated with book.
 */
QList<Theme> Collection::getBooksThemes(int id) throw(DataBaseException)
{
	PreparedStatement themes("SELECT * FROM themes WHERE id IN (%1)", db->getType());
	string themesbooks("SELECT themesid FROM booksthemes WHERE booksid = %1");
	themes.arg(themesbooks);
	themes.arg(id);
	
	ResultSet rs = db->query(themes);
	return parseThemeResultSet(rs);
}

/**
 * @brief Gets the translator of a given book.
 *
 * @param id id of book whose translator is desired.
 *
 * @return Author associated with this book as translator.
 */
Author Collection::getBooksTranslator(int id) throw(DataBaseException)
{
	PreparedStatement translator("SELECT * FROM authors WHERE id = '%1'", db->getType());
	translator.arg(id);

	ResultSet rs = db->query(translator);
	QList<Author> aList = parseAuthorResultSet(rs);

	if(aList.empty())
		return Author();
	else
		return aList.first();
}

/**
 * @brief Creates a query to search for author.
 *
 * @param field In what field the search should be done
 * @param name What should be searched for.
 *
 * @return Returns a PreparedStatement containing a query ready to be executed.
 *
 * @exception DataBaseException Possible error when creating PreparedStatement.
 *
 * Creates a PreparedStatement containing a query that selects all field from the
 * authors table. The query searches for \a name in \a field by aproximation.
 * The supported fields are first name, last name, description, critique, rating,
 * picture. If you want to search by theme see \a compositeSearchAuthors().
 */
PreparedStatement Collection::simpleSearchAuthors(Author::author_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("SELECT * FROM authors WHERE %1 LIKE '%%2%'", db->getType());
	if(field == Author::a_firstname)
		query.arg("firstname");
	else if(field == Author::a_lastname)
		query.arg("lastname");
	else if(field == Author::a_description)
		query.arg("description");
	else if(field == Author::a_critique)
		query.arg("critique");
	else if(field == Author::a_rating)
		query.arg("rating");
	else if(field == Author::a_picture)
		query.arg("picture");

	query.arg(name);
	return query;
}

/**
 * @brief Creates a query to search for author.
 *
 * @param field In what field the search should be done
 * @param name What should be searched for.
 *
 * @return Returns a PreparedStatement containing a query ready to be executed.
 *
 * @exception DataBaseException Possible error when creating PreparedStatement.
 *
 * Creates a PreparedStatement containing a query that will select every field of
 * the authors table. Currently the only supported field is themes, the result of
 * this query will be all authors associated with themes whose name contain \a name.
 */
PreparedStatement Collection::compositeSearchAuthors(Author::author_field field, string name) throw(DataBaseException)
{
	PreparedStatement query("SELECT * FROM authors WHERE id IN (SELECT authorsid FROM authors%1 WHERE %2id IN (SELECT id FROM %3 WHERE %4 LIKE '%%5%'))", db->getType());
	if(field == Author::a_themes)
	{
		query.arg("themes");
		query.arg("themes");
		query.arg("themes");
		query.arg("name");
		query.arg(name);
	}
	
	return query;
}

/**
 * @brief Transforms the result set in to a QList.
 *
 * @param rs ResultSet to be processed.
 *
 * @return QList of authors described in \a rs.
 *
 * @exception DataBaseException Possible error when steping through ResultSet.
 *
 * @warning The ResultSet MUST contain every field in the authors table.
 */
QList<Author> Collection::parseAuthorResultSet(ResultSet &rs) throw(DataBaseException)
{
	QList<Author> authorList;
	while(rs.nextRow())
	{
		Author a;
		a.setId(rs.getInt("id"));
		a.setFirstName(rs.getString("firstname"));
		a.setLastName(rs.getString("lastname"));
		a.setDescription(rs.getString("description"));
		a.setCritique(rs.getString("critique"));
		a.setRating(rs.getInt("rating"));
		a.setPicture(rs.getString("picture"));
		a.setThemes(getAuthorsThemes(rs.getInt("id")));
		authorList.append(a);
	}
	return authorList;
}

/**
 * @brief Returns all themes associated with a given author.
 *
 * @param id id of the author whose themes are desired.
 *
 * @return QList of all themes referenced by given author id.
 *
 * @exception DataBaseException Possible error when creating PreparedStatement,
 * executing query or parsing results.
 */
QList<Theme> Collection::getAuthorsThemes(int id) throw(DataBaseException)
{
	PreparedStatement themes("SELECT * FROM themes WHERE id IN (%1)", db->getType());
	string themesauthors("SELECT themesid FROM authorsthemes WHERE authorsid = %1");
	themes.arg(themesauthors);
	themes.arg(id);
	
	ResultSet rs = db->query(themes);
	return parseThemeResultSet(rs);
}

PreparedStatement Collection::simpleSearchPublishers(Publisher::publisher_field field, string name) throw(DataBaseException)
{
	return PreparedStatement("", db->getType());
}

PreparedStatement Collection::compositeSearchPublishers(Publisher::publisher_field field, string name) throw(DataBaseException)
{
	return PreparedStatement("", db->getType());
}

QList<Publisher> Collection::parsePublisherResultSet(ResultSet &rs) throw(DataBaseException)
{
	return QList<Publisher>();
}

/**
 * @brief Transform a result set into a QList.
 *
 * @param rs ResultSet to be parsed.
 *
 * @return Returns a QList of themes containing all themes in the result set(possibly 0).
 *
 * @warning The query that originated \a rs must contain ALL fields in the themes
 * table.
 */
QList<Theme> Collection::parseThemeResultSet(ResultSet &rs) throw(DataBaseException)
{
	QList<Theme> themeList;
	while(rs.nextRow())
	{
		Theme t;
		t.setId(rs.getInt("id"));
		t.setName(rs.getString("name"));
		t.setDescription(rs.getString("description"));
		themeList.append(t);
	}
	return themeList;
}
