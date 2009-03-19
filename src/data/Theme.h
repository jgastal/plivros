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

	private:
		static void initHeaders();
		QString name;
} ;

#endif /* THEME_H_ */
