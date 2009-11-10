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
 * @file SearchForm.cpp
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "SearchForm.h"

#include <QMessageBox>

#include "PropertiesGroupBox.h"
#include "MessageBoxDataBaseException.h"
#include "Section.h"

#include "Collection.h"
#include "DataBaseException.h"

#include "Data.h"

SearchForm::SearchForm(Section::section t, Collection *c, QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	propertiesGroupBox->init(t);
	this->c = c;
	this->t = t;
	connect(closePushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(searchPushButton, SIGNAL(clicked()), this, SLOT(search()));

	connect(tableWidget, SIGNAL(edit(int)), this, SIGNAL(edit(int)));
	connect(tableWidget, SIGNAL(del(int)), this, SIGNAL(del(int)));
	connect(tableWidget, SIGNAL(view(int)), this, SIGNAL(view(int)));
}

Section::section SearchForm::getType() const
{
	return t;
}

void SearchForm::search()
{
	unsigned short int prop;
	try
	{
		prop = propertiesGroupBox->getSelectedRadioButton();
		if(t == Section::Book)
		{
			QList<Book> bList = c->searchBooks(Book::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(bList);
		}
		else if(t == Section::Author)
		{
			QList<Author> aList = c->searchAuthors(Author::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(aList);
		}
		else if(t == Section::Publisher)
		{
			QList<Publisher> pList = c->searchPublishers(Publisher::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(pList);
		}
		else if(t == Section::Theme)
		{
			QList<Theme> tList = c->searchThemes(Theme::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(tList);
		}
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException mbdbe(&dbe, this);
		mbdbe.appendText("Unable to perform requested search.");
		mbdbe.exec();
	}
	catch(std::out_of_range ofr)
	{
		QMessageBox mb(this);
		mb.setIcon(QMessageBox::Warning);
		mb.setWindowTitle(tr("Warning"));
		mb.setText(tr("You must select a property in which to search."));
		mb.setStandardButtons(QMessageBox::Ok);
		mb.exec();
		return;
	}
}

void SearchForm::search(unsigned short int where, QString what)
{
	try
	{
		propertiesGroupBox->setSelectedRadioButton(where);
		searchLineEdit->setText(what);
		search();
	}
	catch(std::out_of_range e)
	{
		QMessageBox mb(this);
		mb.setIcon(QMessageBox::Warning);
		mb.setWindowTitle(tr("Warning"));
		mb.setText(tr("Property selection error."));
		mb.setStandardButtons(QMessageBox::Ok);
		mb.exec();
		return;
	}
}
