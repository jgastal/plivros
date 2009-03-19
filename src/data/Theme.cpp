/**
 * @file Theme.cpp
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#include <QString>

#include "Theme.h"
#include "DataObject.h"

Theme::Theme() : DataObject("", 0)
{
	setName("");
	if(!propertiesCount)
		Theme::initHeaders();
}

Theme::Theme(QString nm, QString desc, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
	if(!propertiesCount)
		Theme::initHeaders();
}

QString Theme::getName() const
{
	return name;
}

void Theme::setName(const QString name)
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
	prop << getName() << getDescription();
	return prop;
}

void Theme::initHeaders()
{
	headers << QT_TR_NOOP("Name") << QT_TR_NOOP("Description");
	propertiesCount = 2;
}
