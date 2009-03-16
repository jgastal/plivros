/**
 * @file AddPublisher.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "AddPublisher.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Publisher.h"
#include "Theme.h"

AddPublisher::AddPublisher(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	connect(addPushButton, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
	connect(logoPushButton, SIGNAL(clicked(bool)), this, SLOT(logoFileChooser()));
}

///@brief Closes the tab that owns this form.
void AddPublisher::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

///@brief Adds publisher described in the form.
void AddPublisher::add()
{
	if(!validateInput())
		return;
	Publisher p;
	p.setName(nameLineEdit->text().toStdString());
	p.setDescription(descriptionLineEdit->text().toStdString());
	p.setCritique(critiqueLineEdit->text().toStdString());
	p.setLogo(logoLineEdit->text().toStdString());

	p.setThemes(getSelectedThemes());

	try
	{
		c->insertPublisher(p);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your publisher has not been added."));
		q.exec();
	}
	close();
}

bool AddPublisher::validateInput()
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

QList<Theme> AddPublisher::getSelectedThemes()
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
void AddPublisher::populateThemesListWidget()
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
void AddPublisher::logoFileChooser()
{
	QFileDialog d(this);
	d.setFileMode(QFileDialog::ExistingFile);
	d.setViewMode(QFileDialog::Detail);
	d.exec();
	QStringList strList = d.selectedFiles();
	if(strList.count())
		logoLineEdit->setText(strList.first());
}
