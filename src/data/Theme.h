/**
 * @file Theme.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef THEME_H_
#define THEME_H_

#include "DataObject.h"

#include <string>

using namespace std;

class Theme : public DataObject
{
	public:
		Theme();
		Theme(string nm, string desc, unsigned int id = 0);
		string getName() const;
		void setName(const string name);
		bool operator==(const Theme &t) const;

		enum theme_field
		{
			t_name,
			t_description
		};

	private:
		string name;
} ;

#endif /* THEME_H_ */
