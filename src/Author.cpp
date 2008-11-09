/**
 * @file Author.cpp
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#include <string>

#include <QtCore/QList>

#include "Author.h"

using namespace std;

Author::Author(string fn, string ln, string desc, string cri,
	unsigned short int rat, string pic, QList<Theme*> t, unsigned int id)
{
	setFirstName(fn);
	setLastName(ln);
	setDescription(desc);
	setCritique(cri);
	setRating(rat);
	setPicture(pic);
	setThemes(t);
	setId(id);
}

unsigned int Author::getId() const
{
	return id;
}

void Author::setId(unsigned int id)
{
	this->id = id;
}

string Author::getFirstName() const
{
	return FirstName;
}

void Author::setFirstName(string FirstName)
{
	this->FirstName = FirstName;
}

string Author::getLastName() const
{
	return LastName;
}

void Author::setLastName(string LastName)
{
	this->LastName = LastName;
}

string Author::getDescription() const
{
	return Description;
}

void Author::setDescription(string Description)
{
	this->Description = Description;
}

string Author::getCritique() const
{
	return Critique;
}

void Author::setCritique(string Critique)
{
	this->Critique = Critique;
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

QList<Theme*> Author::getThemes() const
{
	return themes;
}

void Author::setThemes(QList<Theme*> themes)
{
	this->themes = themes;
}
