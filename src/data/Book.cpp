/**
 * @file Book.cpp
 *
 * @date Nov 1, 2008
 * @author Jonas M. Gastal
 */

#include <QDate>
#include <QString>
#include <QList>
#include <QStringList>

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"
#include "DataObject.h"

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
	if(!propertiesCount)
		Book::initHeaders();
}

Book::Book(char isbn[13], QString title, unsigned short int ed, QString cri,
	QString desc, unsigned short int rat, QString cov, QString eb, QDate d,
	QString UDC, QList<Author> a, const Author &tr, QList<Publisher> p,
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
	if(!propertiesCount)
		Book::initHeaders();
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

QString Book::getTitle() const
{
	return title;
}

void Book::setTitle(QString title)
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

QString Book::getCritique() const
{
	return critique;
}

void Book::setCritique(QString critique)
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

QString Book::getCover() const
{
	return cover;
}

void Book::setCover(QString cover)
{
	this->cover = cover;
}

QString Book::getEbook() const
{
	return ebook;
}

void Book::setEbook(QString ebook)
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

QString Book::getUDC() const
{
	return UDC;
}

void Book::setUDC(QString UDC)
{
	this->UDC = UDC;
}

QList<Author> Book::getAuthors() const
{
	return authors;
}

QString Book::getAuthorsNames() const
{
	QString str("");
	for(QList<Author>::const_iterator it = authors.begin(); it != authors.end(); it++)
	{
		QString name("");
		name.append(translator.getLastName()).append(", ");
		name.append(translator.getFirstName());
		str.append(name).append("; ");
	}
}

void Book::setAuthors(QList<Author> authors)
{
	this->authors = authors;
}

Author Book::getTranslator() const
{
	return translator;
}

QString Book::getTranslatorName() const
{
	QString ret("");
	ret.append(translator.getLastName()).append(", ");
	ret.append(translator.getFirstName());
	return ret;
}

void Book::setTranslator(const Author &tr)
{
	this->translator = tr;
}

QList<Publisher> Book::getPublishers() const
{
	return publishers;
}

QString Book::getPublishersNames() const
{
	QString str("");
	for(QList<Publisher>::const_iterator it = publishers.begin(); it != publishers.end(); it++)
		str.append(it->getName()).append("; ");
}

void Book::setPublishers(QList<Publisher> publishers)
{
	this->publishers = publishers;
}

QList<Theme> Book::getThemes() const
{
	return themes;
}

QString Book::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName()).append("; ");
}

void Book::setThemes(QList<Theme> themes)

{
	this->themes = themes;
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
	prop << getIsbn() << getTitle() << QString::number(getEdition()) << getCritique();
	prop << getDescription() << QString::number(getRating()) << getCover() << getEbook();
	prop << getPubDate().toString() << getUDC() << getAuthorsNames();
	prop << getTranslatorName() << getPublishersNames() << getThemesNames();
	return prop;
}

void Book::initHeaders()
{
	headers << QT_TR_NOOP("ISBN") << QT_TR_NOOP("Title") << QT_TR_NOOP("Edition");
	headers << QT_TR_NOOP("Critique") << QT_TR_NOOP("Description");
	headers << QT_TR_NOOP("Cover") << QT_TR_NOOP("E-Book");
	headers << QT_TR_NOOP("Publishing Date") << QT_TR_NOOP("U.D.C.");
	headers << QT_TR_NOOP("Authors") << QT_TR_NOOP("Translator");
	headers << QT_TR_NOOP("Publishers") << QT_TR_NOOP("Themes");
	propertiesCount = 13;
}
