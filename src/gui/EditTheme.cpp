/**
 * @file EditTheme.cpp
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QMessageBox>

#include "ThemeForm.h"
#include "EditTheme.h"

#include "MainWindow.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

EditTheme::EditTheme(Collection *c, Theme t, QWidget *parent) : ThemeForm(c, parent)
{
	this->t = t;
	nameLineEdit->setText(t.getName().c_str());
	descriptionLineEdit->setText(t.getDescription().c_str());
}

///@brief Updates the theme described in the form(if validated).
void EditTheme::save()
{
	if(!validateInput())
		return;
	t.setName(nameLineEdit->text().toStdString());
	t.setDescription(descriptionLineEdit->text().toStdString());
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
	close();
}
