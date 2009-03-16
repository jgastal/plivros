/**
 * @file ThemeForm.h
 *
 * @date 16/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef THEMEFORM_H
#define THEMEFORM_H

#include "ui_ThemeForm.h"

class Collection;

/**
 * @class ThemeFOrm ThemeForm.h
 *
 * @brief This widget is a form to add a theme.
 */
class ThemeForm : public QWidget, protected Ui::ThemeForm
{
	Q_OBJECT

	public:
		ThemeForm(Collection *c, QWidget *parent = 0);

	protected slots:
		void close();

	protected:
		bool validateInput();
		QWidget *parent;
		Collection *c;
} ;

#endif //ADDTHEME_H
