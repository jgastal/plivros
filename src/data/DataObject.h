#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QString>
#include <QStringList>

class DataObject
{
	public:
		DataObject(const QString desc, const unsigned int id = 0);
		unsigned int getId() const;
		void setId(const unsigned int id);
		QString getDescription() const;
		void setDescription(const QString description);
		virtual QStringList getProperties() const = 0;

		static unsigned short int getPropertiesCount();
		static QStringList getHeaders();
		static void initHeaders();

	protected:
		unsigned int id;
		QString description;

		static QStringList headers;
		static unsigned short int propertiesCount;
} ;

#endif //DATAOBJECT_H
