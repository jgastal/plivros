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

using namespace std;

Author::Author()
{
	setFirstName("");
	setLastName("");
	setDescription("");
	setCritique("");
	setRating(0);
	setPicture("");
	setThemes(QList<Theme>());
	this->id = 0;
}

Author::Author(string fn, string ln, string desc, string cri,
	unsigned short int rat, string pic, QList<Theme> t, unsigned int id)
{
	setFirstName(fn);
	setLastName(ln);
	setDescription(desc);
	setCritique(cri);
	setRating(rat);
	setPicture(pic);
	setThemes(t);
	this->id = id;
}

unsigned int Author::getId() const
{
	return id;
}

void Author::setId(unsigned int id)
{
	if(this->id == 0) //If id has never been set.
		this->id = id;
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

string Author::getDescription() const
{
	return description;
}

void Author::setDescription(string Description)
{
	this->description = description;
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
	if(firstName == a.getFirstName() && lastName == a.getLastName() && 
		description == a.getDescription() && critique == a.getCritique()
		&& rating == a.getRating() && picture == a.getPicture() &&
		themes == a.getThemes())
		return true;
	return false;
}
