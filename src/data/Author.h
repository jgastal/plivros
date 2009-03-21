/**
 * @file Author.h
 *
 * @date Oct 31, 2008
 * @author Jonas M. Gastal
 */

#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <QString>
#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

class Author : public DataObject
{
	public:
		Author();
		Author(QString fn, QString ln, QString desc, QString cri,
			unsigned short int rat, QString pic, QList<Theme> t,
			unsigned int id = 0);
		QString getFirstName() const;
		void setFirstName(QString);
		QString getLastName() const;
		void setLastName(QString);
		QString getCritique() const;
		void setCritique(QString);
		unsigned short int getRating() const;
		void setRating(unsigned short int);
		QString getPicture() const;
		void setPicture(QString);
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
		static author_field getHeader(unsigned short int i);

	private:
		static void initHeaders();
		QString firstName;
		QString lastName;
		QString critique;
		unsigned short int rating;
		QString picture; //path to picture of author
		QList<Theme> themes; //List of themes
};

#endif /* AUTHOR_H_ */
