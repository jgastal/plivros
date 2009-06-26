/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
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
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	connect(savePushButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(cancelPushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(logoPushButton, SIGNAL(clicked()), this, SLOT(logoFileChooser()));
}

bool PublisherForm::validateInput()
{
	if(!nameLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setWindowTitle(tr("Invalid input"));
	q.setText(tr("You must enter the publisher's name."));
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
		themeList = c->getThemes();
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
