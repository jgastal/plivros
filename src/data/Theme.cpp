/**
 * @file Theme.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <string>

using namespace std;

#include "Theme.h"
#include "DataObject.h"

Theme::Theme() : DataObject("", 0)
{
	setName("");
}

Theme::Theme(string nm, string desc, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
}

string Theme::getName() const
{
	return name;
}

void Theme::setName(const string name)
{
	this->name = name;
}

bool Theme::operator==(const Theme &t) const
{
	if(getName() == t.getName() && getDescription() == t.getDescription() && getId() == t.getId())
		return true;
	return false;
}
