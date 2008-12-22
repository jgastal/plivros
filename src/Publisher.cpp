/**
 * @file Publisher.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <string>

#include <QtCore/QList>

#include "Publisher.h"
#include "Theme.h"

using namespace std;

Publisher::Publisher(string nm, string desc, string logo, QList<Theme*> t, unsigned int id)
{
	setName(nm);
	setDescription(desc);
	setLogo(logo);
	setThemes(t);
	setId(id);
}

unsigned int Publisher::getId() const
{
	return id;
}

void Publisher::setId(unsigned int id)
{
	if(this->id == 0) //If id has never been set.
		this->id = id;
}

string Publisher::getName() const
{
	return name;
}

void Publisher::setName(string name)
{
	this->name = name;
}

string Publisher::getDescription() const
{
	return description;
}

void Publisher::setDescription(string description)
{
	this->description = description;
}

string Publisher::getCritique() const
{
	return critique;
}

void Publisher::setCritique(string critique)
{
	this->critique = critique;
}

string Publisher::getLogo() const
{
	return logo;
}

void Publisher::setLogo(string logo)
{
	this->logo = logo;
}

QList<Theme*> Publisher::getThemes()
{
	return themes;
}

void Publisher::setThemes(QList<Theme*> themes)
{
	this->themes = themes;
}
