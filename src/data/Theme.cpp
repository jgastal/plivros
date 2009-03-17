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
	initHeaders();
}

Theme::Theme(string nm, string desc, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
	initHeaders();
}

void Theme::initHeaders()
{
	headers << QT_TR_NOOP("Name") << QT_TR_NOOP("Description");
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

QStringList Theme::getProperties() const
{
	QStringList prop;
	//prop << getName() << getDescription();
	return prop;
}
