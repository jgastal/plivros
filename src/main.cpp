#include <iostream>

#include "Collection.h"
#include "IniParser.h"

using namespace std;

int main(int argc, char **argv)
{
	//Collection c("DefaultUser");
	//std::cout << "Not yet implemented." << std::endl;
	IniParser ini("config.ini");

	string section;
	while((section = ini.getNextSection()) != "")
	{
		cout << "CurrentSection: " << section << endl;
		cout << "field0 = " << ini.getValue("field0") << endl;
		cout << "field1 = " << ini.getValue("field1") << endl;
	}
}
