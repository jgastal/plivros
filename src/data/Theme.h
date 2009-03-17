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

class Theme
{
	public:
		Theme();
		Theme(string nm, string desc, unsigned int id = 0);
		unsigned int getId() const;
		void setId(unsigned int id);
		string getName() const;
		void setName(string name);
		string getDescription() const;
		void setDescription(string description);
		bool operator==(const Theme t) const;

		enum theme_field
		{
			t_name,
			t_description
		};

	private:
		unsigned int id;
		string name;
		string description;
} ;

#endif /* THEME_H_ */
