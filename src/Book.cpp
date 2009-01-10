/**
 * @file Book.cpp
 *
 * @date Nov 1, 2008
 * @author Jonas M. Gastal
 */

#include <string>

#include <QtCore/QDate>
#include <QtCore/QList>

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

using namespace std;

Book::Book()
{
	setIsbn("\0");
	setTitle("");
	setEdition(0);
	setCritique("");
	setDescription("");
	setRating(0);
	setCover("");
	setEbook("");
	setPubDate(QDate());
	setUDC("");
	setAuthors(QList<Author>());
	setTranslator(Author());
	setPublishers(QList<Publisher>());
	setThemes(QList<Theme>());
	this->id = 0;
}

Book::Book(char isbn[13], string title, unsigned short int ed, string cri,
	string desc, unsigned short int rat, string cov, string eb, QDate d,
	string UDC, QList<Author> a, Author tr, QList<Publisher> p,
	QList<Theme> t, unsigned int id)
{
	setIsbn(isbn);
	setTitle(title);
	setEdition(ed);
	setCritique(cri);
	setDescription(desc);
	setRating(rat);
	setCover(cov);
	setEbook(eb);
	setPubDate(d);
	setUDC(UDC);
	setAuthors(a);
	setTranslator(tr);
	setPublishers(p);
	setThemes(t);
	this->id = id;
}

unsigned int Book::getId() const
{
	return id;
}

void Book::setId(unsigned int id)
{
	if(this->id == 0) //If id has never been set.
		this->id = id;
}

const char* Book::getIsbn() const
{
	return isbn;
}

void Book::setIsbn(char isbn[13])
{
	memcpy(this->isbn, isbn, 13 * sizeof(char));
	this->isbn[13] = '\0';
}

string Book::getTitle() const
{
	return title;
}

void Book::setTitle(string title)
{
	this->title = title;
}

unsigned short int Book::getEdition() const
{
	return edition;
}

void Book::setEdition(unsigned short int edition)
{
	this->edition = edition;
}

string Book::getCritique() const
{
	return critique;
}

void Book::setCritique(string critique)
{
	this->critique = critique;
}

string Book::getDescription() const
{
	return description;
}

void Book::setDescription(string description)
{
	this->description = description;
}

unsigned short int Book::getRating() const
{
	return rating;
}

void Book::setRating(unsigned short int rating)
{
	this->rating = rating;
}

string Book::getCover() const
{
	return cover;
}

void Book::setCover(string cover)
{
	this->cover = cover;
}

string Book::getEbook() const
{
	return ebook;
}

void Book::setEbook(string ebook)
{
	this->ebook = ebook;
}

QDate Book::getPubDate() const
{
	return pubDate;
}

void Book::setPubDate(QDate pubDate)
{
	this->pubDate = pubDate;
}

string Book::getUDC() const
{
	return UDC;
}

void Book::setUDC(string UDC)
{
	this->UDC = UDC;
}

QList<Author> Book::getAuthors() const
{
	return authors;
}

void Book::setAuthors(QList<Author> authors)
{
	this->authors = authors;
}

Author Book::getTranslator() const
{
    return translator;
}

void Book::setTranslator(Author translator)
{
    this->translator = translator;
}

QList<Publisher> Book::getPublishers() const
{
	return publishers;
}

void Book::setPublishers(QList<Publisher> publishers)
{
	this->publishers = publishers;
}

QList<Theme> Book::getThemes() const
{
	return themes;
}

void Book::setThemes(QList<Theme> themes)

{
	this->themes = themes;
}
