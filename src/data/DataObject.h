#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <string>
#include <QStringList>

using namespace std;

class DataObject
{
	public:
		DataObject(const string desc, const unsigned int id = 0);
		unsigned int getId() const;
		void setId(const unsigned int id);
		string getDescription() const;
		void setDescription(const string description);
		unsigned short int getPropertiesCount() const;
		void setPropertiesCount(unsigned short int c);
		QStringList getHeaders() const;
		virtual QStringList getProperties() const = 0;
		

	protected:
		virtual void initHeaders() = 0;
		unsigned int id;
		unsigned short int propertiesCount;
		string description;
		QStringList headers;
} ;

#endif //DATAOBJECT_H
