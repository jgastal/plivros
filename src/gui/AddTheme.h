/**
 * @file AddTheme.h
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef ADDTHEME_H
#define ADDTHEME_H

#include "ThemeForm.h"

class Collection;

/**
 * @class AddTheme AddTheme.h
 *
 * @brief This widget is a form to add a theme.
 */
class AddTheme : public ThemeForm
{
	Q_OBJECT

	public:
		AddTheme(Collection *c, QWidget *parent = 0);

	private slots:
		void save();
} ;

#endif //ADDTHEME_H
