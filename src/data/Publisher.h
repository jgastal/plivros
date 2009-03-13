/**
 * @file Publisher.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <string>

#include <QtCore/QList>

#include "Theme.h"

using namespace std;

class Publisher
{
	public:
		Publisher();
		Publisher(string nm, string desc, string cri, string logo, QList<Theme> t,
			unsigned int id = 0);
		unsigned int getId() const;
		void setId(unsigned int id);
		string getName() const;
		void setName(string name);
		string getDescription() const;
		void setDescription(string description);
		string getCritique() const;
		void setCritique(string critique);
		string getLogo() const;
		void setLogo(string logo);
		QList<Theme> getThemes();
		void setThemes(QList<Theme> themes);

		enum publisher_field
		{
			p_name,
			p_description,
			p_critique,
			p_logo,
			p_themes
		};

	private:
		unsigned int id;
		string name;
		string description;
		string critique;
		string logo;
		QList<Theme> themes;
};

#endif /* PUBLISHER_H_ */
