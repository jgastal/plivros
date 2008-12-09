 /**
  * @file IniParser.cpp
  * @brief Source containing definition of IniParser methods.
  */

#include "IniParser.h"
#include <string>
#include <list>
#include <map>
using namespace std;

/**
 * @brief Opens and parses ini file.
 *
 * @param path pointing to file to be parsed.
 *
 * The constructor parses the file by looping through each line of the file
 * that is not blank or a comment. If the line contains '[' it indicates a
 * new session otherwise a new value in the current section.
 */
IniParser::IniParser(string path)
{
	string line, tmp;
	string field, value;
	size_t fieldEnd, valueStart, start, commentStart;
	ifstream ini;
	ini.exceptions(fstream::eofbit | fstream::failbit | fstream::badbit);
	ini.open(path.c_str(), fstream::in | fstream::out);

	int sectionNum = 0;

	while(!ini.eof())
	{
		getline(ini, line);
		start = line.find_first_not_of("\t\r\n ");
		if(start == string::npos || line.at(start) == ';') //coment
			continue;

		if(line.find('[') != string::npos)
		{
			//Only checks what is between brackets(not really comment)
			commentStart = line.find(']', 0);
			tmp = line.substr(1, commentStart - 1); //removing enclosing brackets
			values[tmp];
			sectionNum++;
		}
		else if(sectionNum)
		{
			fieldEnd = line.find_first_of(" \t\r\n=");
			field = line.substr(0, fieldEnd);
			valueStart = line.find_first_not_of(" \t\r\n=", fieldEnd);
			commentStart = line.find_first_of(" \t\r\n;", valueStart);
			value = line.substr(valueStart, commentStart - valueStart);
			values[tmp][field] = value;
		}
	}
	currentSection = "";
}

///@brief Clears all values of all sections.
IniParser::~IniParser()
{
	ini_map::iterator it;
	for(it = values.begin(); it != values.end(); it++)
		it->second.clear();
	values.clear();
}

/**
 * @brief Goes to next section.
 *
 * @return A string with the name of the next section as order in the map.
 *
 * This method will use the C++ iterator to get the section next to current. In
 * most implementations sections will be kept in alphabetic order.
 */
string IniParser::getNextSection()
{
	ini_map::iterator it;
	if(currentSection == "")
		it = values.begin();
	else
	{
		it = values.find(getCurrentSection());
		++it;
	}
	if(it != values.end())
	{
		currentSection = it->first;
		currentMap = it->second;
		return currentSection;
	}
	return "";
}

/**
 * @brief Goes to the requested section.
 *
 * @param name Name of the section to be set as current.
 *
 * @return Indicator of whether operation was successful.
 *
 * @retval true Operation successful.
 * @retval false Error in operation.
 *
 * This method will make the requested section the current one by using
 * the C++ iterator to find the desired section and set the currentSection
 * and currentMap members.
 */
bool IniParser::goToSection(string name)
{
	ini_map::iterator it;
	if(name == "")
	{
		currentSection = values.begin()->first;
		currentMap = values.begin()->second;
		return true;
	}
	it = values.find(name);
	if(it == values.end())
		return false;
	currentSection = it->first;
	currentMap = it->second;
	return true;
}

/**
 * @brief Gets name of current section.
 *
 * @return String with name of current section .
 *
 * This returns the name of the current section: the one whose values
 * caller will get by using getValue().
 */
string IniParser::getCurrentSection()
{
	return currentSection;
}

/**
 * @brief Yields the value of the requested field of the current section.
 *
 * @param field Name of the field of which value is desired.
 *
 * @return String with the value of field in the current section.
 */
string IniParser::getValue(string field)
{
	if(getCurrentSection() != "")
		return values[getCurrentSection()][field];
}
