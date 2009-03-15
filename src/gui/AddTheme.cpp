/**
 * @file AddTheme.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QMessageBox>

#include "AddTheme.h"

#include "MainWindow.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

AddTheme::AddTheme(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	connect(addPushButton, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

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
		MessageBoxDataBaseException q(this);
		q.appendText(tr("Your theme has not been added."));
		q.exec();
	}
	close();
}

void AddTheme::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

bool AddTheme::validateInput()
{
	if(!nameLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setText(tr("You must enter the theme name."));
	q.setDefaultButton(QMessageBox::Retry);
	q.exec();
	nameLineEdit->setFocus();
	return false;
}
