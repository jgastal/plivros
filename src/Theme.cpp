/**
 * @file Theme.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <string>

using namespace std;

#include "Theme.h"

Theme::Theme()
{
	setName("");
	setDescription("");
	this->id = 0;
}

Theme::Theme(string nm, string desc, unsigned int id)
{
	setName(nm);
	setDescription(desc);
	this->id = id;
}

unsigned int Theme::getId() const
{
	return id;
}

void Theme::setId(unsigned int id)
{
	if(this->id == 0) //If id has never been set.
		this->id = id;
}

string Theme::getName() const
{
	return name;
}

void Theme::setName(string name)
{
	this->name = name;
}

string Theme::getDescription() const
{
	return description;
}

void Theme::setDescription(string description)
{
	this->description = description;
}
