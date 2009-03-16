/**
 * @file ThemeForm.cpp
 *
 * @date 16/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QMessageBox>

#include "ThemeForm.h"

#include "MainWindow.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

ThemeForm::ThemeForm(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

///@brief Closes the tab that owns this form.
void ThemeForm::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

///@brief Makes sure the name has been filed out.
bool ThemeForm::validateInput()
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
