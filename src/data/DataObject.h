/**
 * @file DataObject.h
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QString>
#include <QStringList>

/**
 * @class DataObject DataObject.h
 *
 * @brief Class is pure-virtual super class of all classes that declare data types.
 *
 * DataObject is a abstraction of common properties of all data types. Ideally
 * headers and propertiesCount would be virtual, however I can't  because I can't
 * declare static virtual members.
 */
class DataObject
{
	public:
		DataObject(const QString desc, const unsigned int id = 0);
		unsigned int getId() const;
		void setId(const unsigned int id);
		QString getDescription() const;
		void setDescription(const QString description);
		virtual QStringList getProperties() const = 0;

		static QStringList headers;
		static unsigned short int propertiesCount;

	protected:
		unsigned int id;
		QString description;
} ;

#endif //DATAOBJECT_H
