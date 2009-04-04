/**
 * @file AddTheme.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "ThemeForm.h"
#include "AddTheme.h"

#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

AddTheme::AddTheme(Collection *c, QWidget *parent) : ThemeForm(c, parent)
{
	//just calling parent constructor suffices
}

///@brief Adds the theme described in the form(if validated).
void AddTheme::save()
{
	if(!validateInput())
		return;
	Theme t;
	t.setName(nameLineEdit->text());
	t.setDescription(descriptionLineEdit->text());
	try
	{
		c->insertTheme(t);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("The theme has not been added."));
		q.exec();
	}
	emit closeRequested();
}
