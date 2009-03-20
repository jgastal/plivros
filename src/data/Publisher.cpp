/**
 * @file Publisher.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <QString>
#include <QList>

#include "Publisher.h"
#include "Theme.h"
#include "DataObject.h"

Publisher::Publisher() : DataObject("", 0)
{
	setName("");
	setCritique("");
	setLogo("");
	setThemes(QList<Theme>());
	if(!propertiesCount)
		Publisher::initHeaders();
}

Publisher::Publisher(QString nm, QString desc, QString cri, QString logo, QList<Theme> t, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
	setCritique(cri);
	setLogo(logo);
	setThemes(t);
	if(!propertiesCount)
		Publisher::initHeaders();
}

QString Publisher::getName() const
{
	return name;
}

void Publisher::setName(QString name)
{
	this->name = name;
}

QString Publisher::getCritique() const
{
	return critique;
}

void Publisher::setCritique(QString critique)
{
	this->critique = critique;
}

QString Publisher::getLogo() const
{
	return logo;
}

void Publisher::setLogo(QString logo)
{
	this->logo = logo;
}

QList<Theme> Publisher::getThemes() const
{
	return themes;
}

QString Publisher::getThemesNames() const
{
	QString str("");
	for(QList<Theme>::const_iterator it = themes.begin(); it != themes.end(); it++)
		str.append(it->getName()).append("; ");
	return str;
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

QStringList Publisher::getProperties() const
{
	QStringList prop;
	prop << getName() << getDescription() <<  getCritique() << getLogo();
	prop << getThemesNames();
	return prop;
}

void Publisher::initHeaders()
{
	headers << QT_TR_NOOP("Name") << QT_TR_NOOP("Description");
	headers << QT_TR_NOOP("Critique") << QT_TR_NOOP("Logo") << QT_TR_NOOP("Themes");
	propertiesCount = 5;
}
