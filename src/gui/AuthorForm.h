/**
 * @file AuthorForm.h
 *
 * @date 21/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef AUTHORFORM_H
#define AUTHORFORM_H

#include "ui_AuthorForm.h"

#include "Author.h"

class Collection;

/**
 * @class AuthorForm AuthorForm.h
 *
 * @brief This class is a form containing all authors fields.
 */
class AuthorForm : public QWidget, protected Ui::AuthorForm
{
	Q_OBJECT

	public:
		AuthorForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();
		
	protected slots:
		virtual void save() = 0;
		void picFileChooser();
		
	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		Collection *c;
		QList<Theme> themeList;
		
	signals:
		void closeRequested();
} ;

#endif //AUTHORFORM_H
