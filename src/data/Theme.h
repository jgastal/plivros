/**
 * @file Theme.h
 *
 * @date Nov 2, 2008
 * @author Jonas M. Gastal
 */

#ifndef THEME_H_
#define THEME_H_

#include "DataObject.h"

#include <QString>
#include <QStringList>

class Theme : public DataObject
{
	public:
		Theme();
		Theme(QString nm, QString desc, unsigned int id = 0);
		QString getName() const;
		void setName(const QString name);
		bool operator==(const Theme &t) const;
		QStringList getProperties() const;

		enum theme_field
		{
			t_name,
			t_description
		};
		static theme_field getHeader(unsigned short int i);
		static const QStringList headers;
		static const unsigned short int propertiesCount;

	private:
		QString name;
} ;

#endif /* THEME_H_ */
