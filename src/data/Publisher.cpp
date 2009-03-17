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
#include "DataObject.h"

using namespace std;

Publisher::Publisher() : DataObject("", 0)
{
	setName("");
	setCritique("");
	setLogo("");
	setThemes(QList<Theme>());
}

Publisher::Publisher(string nm, string desc, string cri, string logo, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
	setCritique(cri);
	setLogo(logo);
	setThemes(t);
}

string Publisher::getName() const
{
	return name;
}

void Publisher::setName(string name)
{
	this->name = name;
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

QList<Theme> Publisher::getThemes() const
{
	return themes;
}

void Publisher::setThemes(QList<Theme> themes)
{
	this->themes = themes;
}

bool Publisher::operator==(const Publisher p) const
{
	if(getName() == p.getName() && getDescription() == p.getDescription() &&
		getCritique() == p.getCritique() && getLogo() == p.getLogo() &&
		getThemes() == p.getThemes() && getId() == p.getId())
		return true;
	return false;
}
