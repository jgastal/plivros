/**
 * @file PublisherForm.cpp
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "PublisherForm.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Publisher.h"
#include "Theme.h"

PublisherForm::PublisherForm(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	connect(savePushButton, SIGNAL(clicked(bool)), this, SLOT(save()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
	connect(logoPushButton, SIGNAL(clicked(bool)), this, SLOT(logoFileChooser()));
}

///@brief Closes the tab that owns this form.
void PublisherForm::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

bool PublisherForm::validateInput()
{
	if(!nameLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setText(tr("You must enter the publisher name."));
	q.setDefaultButton(QMessageBox::Retry);
	q.exec();
	nameLineEdit->setFocus();
	return false;
}

QList<Theme> PublisherForm::getSelectedThemes()
{
	QList<Theme> list;
	for(int i = 0; i < themesListWidget->count(); i++)
	{
		if(themesListWidget->item(i)->isSelected())
			list.append(themeList.at(i));
	}
	return list;
}

///@brief Filles themesListWidget with all existing themes.
void PublisherForm::populateThemesListWidget()
{
	try
	{
		themeList = c->searchThemes(Theme::t_name, "");
		QStringList strList;
		for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
			strList.append(it->getName().c_str());
		themesListWidget->clear();
		themesListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of themes.\nClosing this tab."));
		q.exec();
	}
}

///@brief Shows file chooser and puts chosen file in logoLineEdit.
void PublisherForm::logoFileChooser()
{
	QFileDialog d(this);
	d.setFileMode(QFileDialog::ExistingFile);
	d.setViewMode(QFileDialog::Detail);
	d.exec();
	QStringList strList = d.selectedFiles();
	if(strList.count())
		logoLineEdit->setText(strList.first());
}