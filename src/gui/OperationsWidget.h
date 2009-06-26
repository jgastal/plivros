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
#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

#include "Section.h"

class Collection;
class QButtonGroup;
class DataObject;
class Theme;
class Publisher;
class Author;
class Book;

/**
 * @class OperationsWidget OperationgsWidget.h
 *
 * @brief This class contains offers the user access to the apps standard opeartions.
 *
 * This class offers the add and search operations for all four sections(Books,
 * Authors, Publishers, Themes). The add and search buttons actions depend on which
 * section is selected.
 */
class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		OperationsWidget(Collection *c, Section::section s, QWidget *parent = 0);
		void setSection(Section::section s);
		Section::section getType() const;

	public slots:
		void add();
		void edit(DataObject*);
		void erase(DataObject*);
		void view(DataObject*);
		void search();
		void setSectionButton();

	protected slots:
		void closeTab();
		void closeTab(int index);
		void setSection(QAbstractButton *bt);

	private:
		Collection *c;
		QButtonGroup *btGroup;
		Section::section section;

		void createAddThemeForm();
		void createEditThemeForm(Theme *t);
		void createAddPublisherForm();
		void createEditPublisherForm(Publisher *p);
		void createAddAuthorForm();
		void createEditAuthorForm(Author *a);
		void createViewAuthorDetails(Author *a);
		void createAddBookForm();
		void createEditBookForm(Book *b);
		void createViewBookDetails(Book *b);
} ;

#endif //OPERATIONSWIDGET_H
