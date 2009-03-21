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
}

Theme::Theme(QString nm, QString desc, unsigned int id) : DataObject(desc, id)
{
	setName(nm);
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

Theme::theme_field Theme::getHeader(unsigned short int i)
{
	switch(i)
	{
		case t_name:
			return t_name;
		case t_description:
			return t_description;
	}
}

void Theme::initHeaders()
{
	headers << QT_TR_NOOP("Name") << QT_TR_NOOP("Description");
	propertiesCount = 2;
}
