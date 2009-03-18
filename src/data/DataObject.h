#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QString>
#include <QStringList>

using namespace std;

class DataObject
{
	public:
		DataObject(const QString desc, const unsigned int id = 0);
		unsigned int getId() const;
		void setId(const unsigned int id);
		QString getDescription() const;
		void setDescription(const QString description);
		unsigned short int getPropertiesCount() const;
		QStringList getHeaders() const;
		virtual QStringList getProperties() const = 0;
		

	protected:
		virtual void initHeaders() = 0;
		void setPropertiesCount(unsigned short int c);
		unsigned int id;
		unsigned short int propertiesCount;
		QString description;
		QStringList headers;
} ;

#endif //DATAOBJECT_H
