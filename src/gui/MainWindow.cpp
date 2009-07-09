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
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

/**
 * TODO: searchLabel above searchLineEdit?
 */

#include "CategoryFrame.h"
#include "OperationsWidget.h"
#include "Section.h"
#include "Book.h"

#include "MainWindow.h"

#include "Collection.h"

///@brief Constructor. Creates a collection, setups the gui and connects slots and signals.
MainWindow::MainWindow(QString userName, QMainWindow *parent) : QMainWindow(parent)
{
	c = new Collection(userName);
	setupUi(this);

	connect(quitLabel, SIGNAL(linkActivated(QString)), this, SLOT(close()));

	QString userStr = userLabel->text();
	userStr.replace("<user>", userName);
	userLabel->setText(userStr);

	ow = 0;
	cf = new CategoryFrame(displayWidget);
	connect(cf, SIGNAL(clicked(Section::section)), this, SLOT(createOpsWidget(Section::section)));
	displayWidget->layout()->addWidget(cf);

	connect(searchPushButton, SIGNAL(pressed()), this, SLOT(quickSearch()));
}

MainWindow::~MainWindow()
{
	delete c;
}

void MainWindow::createOpsWidget(Section::section s)
{
	if(!ow)
	{
		ow = new OperationsWidget(c, s, displayWidget);
		displayWidget->layout()->addWidget(ow);
	}
	else
	{
		ow->setSection(s);
		ow->setSectionButton();
	}

	cf->hide();
	ow->show();
}

void MainWindow::home()
{
	if(ow)
		ow->hide();
	cf->show();
}

void MainWindow::quickSearch()
{
	createOpsWidget(Section::Book);
	ow->searchBook(Book::b_title, searchLineEdit->text());
}
