/**
 * @file Theme.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef THEME_H_
#define THEME_H_

#include <string>

using namespace std;

enum theme_field
{
	name,
	description
};

class Theme
{
	public:
		Theme(string nm, string desc, unsigned int id = 0);
		unsigned int getId() const;
		void setId(unsigned int id);
		string getName() const;
		void setName(string name);
		string getDescription() const;
		void setDescription(string description);

	private:
		unsigned int id;
		string name;
		string description;
} ;

#endif /* THEME_H_ */
