/**
 * @file EditTheme.cpp
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "ThemeForm.h"
#include "EditTheme.h"

#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

EditTheme::EditTheme(Collection *c, Theme t, QWidget *parent) : ThemeForm(c, parent)
{
	this->t = t;
	nameLineEdit->setText(t.getName());
	descriptionLineEdit->setText(t.getDescription());
}

///@brief Updates the theme described in the form(if validated).
void EditTheme::save()
{
	if(!validateInput())
		return;
	t.setName(nameLineEdit->text());
	t.setDescription(descriptionLineEdit->text());
	try
	{
		c->updateTheme(t);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your theme has not been added."));
		q.exec();
	}
	emit closeRequested();
}
