/**
 * @file EditTheme.h
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITTHEME_H
#define EDITTHEME_H

#include "ThemeForm.h"

#include "Theme.h"

class Collection;

/**
 * @class EditTheme EditTheme.h
 *
 * @brief This widget is a form to edit a theme.
 */
class EditTheme : public ThemeForm
{
	Q_OBJECT

	public:
		EditTheme(Collection *c, Theme t, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Theme t;
} ;

#endif //ADDTHEME_H
