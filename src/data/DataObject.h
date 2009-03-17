#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <string>

using namespace std;

class DataObject
{
	public:
		DataObject(const string desc, const unsigned int id = 0);
		unsigned int getId() const;
		void setId(const unsigned int id);
		string getDescription() const;
		void setDescription(const string description);

	private:
		unsigned int id;
		string description;
} ;

#endif //DATAOBJECT_H
