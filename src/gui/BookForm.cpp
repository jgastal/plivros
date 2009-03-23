/**
 * @file BookForm.cpp
 *
 * @date 23/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "BookForm.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Data.h"

BookForm::BookForm(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	populatePublishersListWidget();
	populateAuthorsListWidget();
	populateTranslatorListWidget();
	connect(savePushButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(cancelPushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(coverPushButton, SIGNAL(clicked()), this, SLOT(coverFileChooser()));
	connect(ebookPushButton, SIGNAL(clicked()), this, SLOT(ebookFileChooser()));
}

bool BookForm::validateInput()
{
	if(!titleLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setWindowTitle(tr("Invalid input"));
	q.setText(tr("You must enter the books's title."));
	q.setDefaultButton(QMessageBox::Retry);
	q.exec();
	titleLineEdit->setFocus();
	return false;
}

///@brief Returns the themes that are marked in the themesListWidget.
QList<Theme> BookForm::getSelectedThemes()
{
	QList<Theme> list;
	for(int i = 0; i < themesListWidget->count(); i++)
	{
		if(themesListWidget->item(i)->isSelected())
			list.append(themeList.at(i));
	}
	return list;
}

///@brief Fills themesListWidget with all existing themes.
void BookForm::populateThemesListWidget()
{
	try
	{
		themeList = c->searchThemes(Theme::t_name, "");
		QStringList strList;
		for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
			strList.append(it->getName());
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

///@brief Returns the publishers that are marked in the publishersListWidget.
QList<Publisher> BookForm::getSelectedPublishers()
{
	QList<Publisher> list;
	for(int i = 0; i < publisherListWidget->count(); i++)
	{
		if(publisherListWidget->item(i)->isSelected())
			list.append(publisherList.at(i));
	}
	return list;
}

///@brief Fills publishersListWidget with all existing publishers.
void BookForm::populatePublishersListWidget()
{
	try
	{
		publisherList = c->searchPublishers(Publisher::p_name, "");
		QStringList strList;
		for(QList<Publisher>::iterator it = publisherList.begin(); it != publisherList.end(); it++)
			strList.append(it->getName());
		publisherListWidget->clear();
		publisherListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of publishers.\nClosing this tab."));
		q.exec();
	}
}

///@brief Returns the authors that are marked in the authorsListWidget.
QList<Author> BookForm::getSelectedAuthors()
{
	QList<Author> list;
	for(int i = 0; i < authorsListWidget->count(); i++)
	{
		if(authorsListWidget->item(i)->isSelected())
			list.append(authorList.at(i));
	}
	return list;
}

///@brief Fills authorsListWidget with all existing authors.
void BookForm::populateAuthorsListWidget()
{
	try
	{
		authorList = c->searchAuthors(Author::a_description, "");
		QStringList strList;
		for(QList<Author>::iterator it = authorList.begin(); it != authorList.end(); it++)
		{
			QString str("");
			str.append(it->getLastName()).append(", ").append(it->getFirstName());
			strList.append(str);
		}
		authorsListWidget->clear();
		authorsListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of authors.\nClosing this tab."));
		q.exec();
	}
}

Author BookForm::getSelectedTranslator()
{
	Author a;
	for(int i = 0; i < translatorListWidget->count(); i++)
	{
		if(authorsListWidget->item(i)->isSelected())
			a = authorList.at(i);
	}
	return a;
}

///@brief Fills authorsListWidget with all existing authors.
void BookForm::populateTranslatorListWidget()
{
	try
	{
		QStringList strList;
		for(QList<Author>::iterator it = authorList.begin(); it != authorList.end(); it++)
		{
			QString str("");
			str.append(it->getLastName()).append(", ").append(it->getFirstName());
			strList.append(str);
		}
		translatorListWidget->clear();
		translatorListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of translators.\nClosing this tab."));
		q.exec();
	}
}

///@brief Shows file chooser and puts chosen file in coverLineEdit.
void BookForm::coverFileChooser()
{
	QFileDialog d(this);
	d.setFileMode(QFileDialog::ExistingFile);
	d.setViewMode(QFileDialog::Detail);
	d.exec();
	QStringList strList = d.selectedFiles();
	if(strList.count())
		coverLineEdit->setText(strList.first());
}

///@brief Shows file chooser and puts chosen file in ebookLineEdit.
void BookForm::ebookFileChooser()
{
	QFileDialog d(this);
	d.setFileMode(QFileDialog::ExistingFile);
	d.setViewMode(QFileDialog::Detail);
	d.exec();
	QStringList strList = d.selectedFiles();
	if(strList.count())
		ebookLineEdit->setText(strList.first());
}
