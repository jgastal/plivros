/**
 * @file Author.cpp
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#include <QString>
#include <QList>

#include "Author.h"
#include "Theme.h"
#include "DataObject.h"

Author::Author() : DataObject("", 0)
{
	setFirstName("");
	setLastName("");
	setCritique("");
	setRating(0);
	setPicture("");
	setThemes(QList<Theme>());
	if(!propertiesCount)
		Author::initHeaders();
}

Author::Author(QString fn, QString ln, QString desc, QString cri,
	unsigned short int rat, QString pic, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setFirstName(fn);
	setLastName(ln);
	setCritique(cri);
	setRating(rat);
	setPicture(pic);
	setThemes(t);
	if(!propertiesCount)
		Author::initHeaders();
}

QString Author::getFirstName() const
{
	return firstName;
}

void Author::setFirstName(QString FirstName)
{
	this->firstName = firstName;
}

QString Author::getLastName() const
{
	return lastName;
}

void Author::setLastName(QString lastName)
{
	this->lastName = lastName;
}
QString Author::getCritique() const
{
	return critique;
}

void Author::setCritique(QString critique)
{
	this->critique = critique;
}

unsigned short int Author::getRating() const
{
	return rating;
}

void Author::setRating(unsigned short int rating)
{
	this->rating = rating;
}

QString Author::getPicture() const
{
	return picture;
}

void Author::setPicture(QString picture)
{
	this->picture = picture;
}

QList<Theme> Author::getThemes() const
{
	return themes;
}

QString Author::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName()).append("; ");
	return str;
}

void Author::setThemes(QList<Theme> themes)
{
	this->themes = themes;
}

bool Author::operator==(const Author a) const
{
	if(firstName == a.getFirstName() && getLastName() == a.getLastName() &&
		getDescription() == a.getDescription() && getCritique() == a.getCritique()
		&& getRating() == a.getRating() && getPicture() == a.getPicture() &&
		getThemes() == a.getThemes() && getId() == a.getId())
		return true;
	return false;
}

QStringList Author::getProperties() const
{
	QStringList prop;
	prop << getFirstName() << getLastName() << getDescription() << getCritique();
	prop << QString::number(getRating()) << getPicture() << getThemesNames();
	return prop;
}

void Author::initHeaders()
{
	headers << QT_TR_NOOP("First Name") << QT_TR_NOOP("Last Name");
	headers << QT_TR_NOOP("Description") << QT_TR_NOOP("Critique");
	headers << QT_TR_NOOP("Rating") << QT_TR_NOOP("Picture");
	headers << QT_TR_NOOP("Themes");
	propertiesCount = 7;
}
