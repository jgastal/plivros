/**
 * @file Publisher.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <QString>
#include <QList>
#include <QStringList>

#include "Theme.h"
#include "DataObject.h"

class Publisher : public DataObject
{
	public:
		Publisher();
		Publisher(QString nm, QString desc, QString cri, QString logo, QList<Theme> t,
			unsigned int id = 0);
		QString getName() const;
		void setName(QString name);
		QString getCritique() const;
		void setCritique(QString critique);
		QString getLogo() const;
		void setLogo(QString logo);
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
		static publisher_field getHeader(unsigned short int i);
		static const QStringList headers;
		static const unsigned short int propertiesCount;

	private:
		QString name;
		QString critique;
		QString logo;
		QList<Theme> themes;
};

#endif /* PUBLISHER_H_ */
