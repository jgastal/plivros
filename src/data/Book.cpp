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
#include "DataObject.h"

using namespace std;

Book::Book() : DataObject("", 0)
{
	setIsbn("\0");
	setTitle("");
	setEdition(0);
	setCritique("");
	setRating(0);
	setCover("");
	setEbook("");
	setPubDate(QDate());
	setUDC("");
	setAuthors(QList<Author>());
	setTranslator(Author());
	setPublishers(QList<Publisher>());
	setThemes(QList<Theme>());
	initHeaders();
}

Book::Book(char isbn[13], string title, unsigned short int ed, string cri,
	string desc, unsigned short int rat, string cov, string eb, QDate d,
	string UDC, QList<Author> a, const Author &tr, QList<Publisher> p,
	QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setIsbn(isbn);
	setTitle(title);
	setEdition(ed);
	setCritique(cri);
	setRating(rat);
	setCover(cov);
	setEbook(eb);
	setPubDate(d);
	setUDC(UDC);
	setAuthors(a);
	setTranslator(tr);
	setPublishers(p);
	setThemes(t);
	initHeaders();
}

void Book::initHeaders()
{
	headers << QT_TR_NOOP("ISBN") << QT_TR_NOOP("Title") << QT_TR_NOOP("Edition");
	headers << QT_TR_NOOP("Critique") << QT_TR_NOOP("Description");
	headers << QT_TR_NOOP("Cover") << QT_TR_NOOP("E-Book");
	headers << QT_TR_NOOP("Publishing Date") << QT_TR_NOOP("U.D.C.");
	headers << QT_TR_NOOP("Authors") << QT_TR_NOOP("Translator");
	headers << QT_TR_NOOP("Publishers") << QT_TR_NOOP("Themes");
}

const char* Book::getIsbn() const
{
	return isbn;
}

void Book::setIsbn(const char isbn[13])
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

void Book::setTranslator(const Author &tr)
{
	this->translator = tr;
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

QString Book::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName().c_str()).append("; ");
}

bool Book::operator==(const Book b) const
{
	if(getIsbn() == b.getIsbn() && getTitle() == b.getTitle() && getEdition() == b.getEdition()
		&& getCritique() == b.getCritique() && getDescription() == b.getDescription()
		&& getRating() == b.getRating() && getCover() == b.getCover() &&
		getEbook() == b.getEbook() && getPubDate() == b.getPubDate() &&
		getUDC() == b.getUDC() && getAuthors() == b.getAuthors() &&
		getTranslator() == b.getTranslator() && getPublishers() == b.getPublishers()
		&& getThemes() == b.getThemes() && getId() == b.getId())
		return true;
	return false;
}

QStringList Book::getProperties() const
{
	QStringList prop;
// 	prop << getIsbn() << getTitle().c_str() << getEdition() << getCritique().c_str();
// 	prop << getDescription().c_str() << getRating() << getCover().c_str() << getEbook().c_str();
// 	prop << getPubDate().toString() << getUDC().c_str() << getAuthorsNames();
// 	prop << getTranslatorName() << getPublishersNames() << getThemesNames();
	return prop;
}
