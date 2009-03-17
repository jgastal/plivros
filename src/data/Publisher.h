/**
 * @file Publisher.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <string>

#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

using namespace std;

class Publisher : public DataObject
{
	public:
		Publisher();
		Publisher(string nm, string desc, string cri, string logo, QList<Theme> t,
			unsigned int id = 0);
		string getName() const;
		void setName(string name);
		string getCritique() const;
		void setCritique(string critique);
		string getLogo() const;
		void setLogo(string logo);
		QList<Theme> getThemes() const;
		QString getThemesNames() const;
		void setThemes(QList<Theme> themes);
		bool operator==(const Publisher p) const;
		QStringList getProperties() const;

		enum publisher_field
		{
			p_name,
			p_description,
			p_critique,
			p_logo,
			p_themes
		};

	private:
		void initHeaders();
		string name;
		string critique;
		string logo;
		QList<Theme> themes;
};

#endif /* PUBLISHER_H_ */
