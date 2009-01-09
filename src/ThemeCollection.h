/**
 * @file ThemeCollection.h
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#ifndef THEMECOLLECTION_H_
#define THEMECOLLECTION_H_

#include <QtCore/QList>

#include "Theme.h"
#include "DataBaseException.h"

class DataBase;

class ThemeCollection
{
	public:
		ThemeCollection(DataBase *db) throw();

		void insertTheme(Theme &t) throw(DataBaseException);
		bool deleteTheme(unsigned int id) throw(DataBaseException);
		void updateTheme(Theme t) throw(DataBaseException);
		QList<Theme> searchThemes(theme_field field, string name);

	private:
		DataBase *db;
};

#endif /* THEMECOLLECTION_H_ */
