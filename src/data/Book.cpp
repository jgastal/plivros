/**
 * @file Book.cpp
 *
 * @date 01/11/2008
 * @author Jonas M. Gastal
 */

#include <QDate>
#include <QString>
#include <QList>
#include <QStringList>

#include "Data.h"
#include "DataObject.h"

const QStringList Book::headers = QStringList() << QT_TR_NOOP("ISBN") <<
QT_TR_NOOP("Title") << QT_TR_NOOP("Edition") << QT_TR_NOOP("Critique") <<
QT_TR_NOOP("Description") << QT_TR_NOOP("Rating") << QT_TR_NOOP("Cover") <<
QT_TR_NOOP("E-Book") << QT_TR_NOOP("Publishing Date") << QT_TR_NOOP("U.D.C.") <<
QT_TR_NOOP("Authors") << QT_TR_NOOP("Translator") << QT_TR_NOOP("Publishers") <<
QT_TR_NOOP("Themes");
const unsigned short int Book::propertiesCount = 14;

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
		name.append(it->getLastName()).append(", ");
		name.append(it->getFirstName());
		str.append(name).append("; ");
	}
	return str;
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
	return str;
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
	return str;
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

Book::book_field Book::getHeader(unsigned short int i)
{
	switch(i)
	{
		case b_isbn:
			return b_isbn;
		case b_title:
			return b_title;
		case b_edition:
			return b_edition;
		case b_critique:
			return b_critique;
		case b_description:
			return b_description;
		case b_rating:
			return b_rating;
		case b_cover:
			return b_cover;
		case b_ebook:
			return b_ebook;
		case b_pubdate:
			return b_pubdate;
		case b_UDC:
			return b_UDC;
		case b_authors:
			return b_authors;
		case b_translator:
			return b_translator;
		case b_publishers:
			return b_publishers;
		case b_themes:
			return b_themes;
	}
}
