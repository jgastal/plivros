/**
 * @file IniParser.h
 * @brief Header containing declaration of IniParser class.
 */

#ifndef INIPARSER_H_
#define INIPARSER_H_

#include <string>
#include <fstream>
#include <list>
#include <map>

using namespace std;

typedef map<string, string> section_map;
typedef map<string, section_map> ini_map;

/**
 * @class IniParser IniParser.h
 *
 * @brief Represents a ini file.
 *
 * This class implements a parser for ini files as specified in:
 * http://en.wikipedia.org/wiki/Ini_file
 * The parser supports comments, ';' indicates a comment.
 * The parser supports looping through sections as well as jumping to
 * the desired section. All values must be inside a section.
 * The parser makes use of the map C++ template, creating a structure
 * representing the ini file upon instantiation of object.
 * All values are returned as strings.
 * Before accessing or setting values getNextSection() or goToSection() must be
 * called.
 */
class IniParser
{
	public:
		IniParser(string path);
		~IniParser();

		string getNextSection();
		bool goToSection(string name = "");
		string getCurrentSection();
		string getValue(string field);
		bool setValue(string field, string value);
		bool removeField(string field);
		bool removeSection(string section);
		bool addSection(string section);
		string* getFields();
		bool saveFile(string path = "");
		bool good();

	private:
		ifstream iniFile;
		string currentSection;
		ini_map values;
		section_map currentMap;
} ;

#endif /*INIPARSER_H_*/
