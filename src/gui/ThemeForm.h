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
 * @class ThemeForm ThemeForm.h
 *
 * @brief This widget is a form to add a theme.
 */
class ThemeForm : public QWidget, protected Ui::ThemeForm
{
	Q_OBJECT

	public:
		ThemeForm(Collection *c, QWidget *parent = 0);

	protected slots:
		virtual void save() = 0;

	protected:
		bool validateInput();
		QWidget *parent;
		Collection *c;

	signals:
		void closeRequested();
} ;

#endif //ADDTHEME_H
