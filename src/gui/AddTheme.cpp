/**
 * @file AddTheme.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QMessageBox>

#include "ThemeForm.h"
#include "AddTheme.h"

#include "MainWindow.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

AddTheme::AddTheme(Collection *c, QWidget *parent) : ThemeForm(c, parent)
{
	pushButton2->setText(tr("Add"));
	connect(pushButton2, SIGNAL(clicked(bool)), this, SLOT(add()));
}

///@brief Adds the theme described in the form(if validated).
void AddTheme::add()
{
	if(!validateInput())
		return;
	Theme t;
	t.setName(nameLineEdit->text().toStdString());
	t.setDescription(descriptionLineEdit->text().toStdString());
	try
	{
		c->insertTheme(t);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your theme has not been added."));
		q.exec();
	}
	close();
}
