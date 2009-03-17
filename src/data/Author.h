/**
 * @file Author.h
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <string>

#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

using namespace std;

class Author : public DataObject
{
	public:
		Author();
		Author(string fn, string ln, string desc, string cri,
			unsigned short int rat, string pic, QList<Theme> t,
			unsigned int id = 0);
		string getFirstName() const;
		void setFirstName(string);
		string getLastName() const;
		void setLastName(string);
		string getCritique() const;
		void setCritique(string);
		unsigned short int getRating() const;
		void setRating(unsigned short int);
		string getPicture() const;
		void setPicture(string);
		QList<Theme> getThemes() const;
		QString getThemesNames() const;
		void setThemes(QList<Theme> themes);
		QStringList getProperties() const;
		bool operator==(const Author a) const;

		enum author_field
		{
			a_firstname,
			a_lastname,
			a_description,
			a_critique,
			a_rating,
			a_picture,
			a_themes
		};

	private:
		void initHeaders();
		string firstName;
		string lastName;
		string critique;
		unsigned short int rating;
		string picture; //path to picture of author
		QList<Theme> themes; //List of themes
};

#endif /* AUTHOR_H_ */
