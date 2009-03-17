/**
 * @file Author.cpp
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#include <string>

#include <QtCore/QList>

#include "Author.h"
#include "Theme.h"
#include "DataObject.h"

using namespace std;

Author::Author() : DataObject("", 0)
{
	setFirstName("");
	setLastName("");
	setCritique("");
	setRating(0);
	setPicture("");
	setThemes(QList<Theme>());
}

Author::Author(string fn, string ln, string desc, string cri,
	unsigned short int rat, string pic, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setFirstName(fn);
	setLastName(ln);
	setCritique(cri);
	setRating(rat);
	setPicture(pic);
	setThemes(t);
}

string Author::getFirstName() const
{
	return firstName;
}

void Author::setFirstName(string FirstName)
{
	this->firstName = firstName;
}

string Author::getLastName() const
{
	return lastName;
}

void Author::setLastName(string lastName)
{
	this->lastName = lastName;
}
string Author::getCritique() const
{
	return critique;
}

void Author::setCritique(string critique)
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

string Author::getPicture() const
{
	return picture;
}

void Author::setPicture(string picture)
{
	this->picture = picture;
}

QList<Theme> Author::getThemes() const
{
	return themes;
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
