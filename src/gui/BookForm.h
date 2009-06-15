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
 * @file BookForm.h
 *
 * @date 23/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef BOOKFORM_H
#define BOOKFORM_H

#include "ui_BookForm.h"

#include "Data.h"

class Collection;

/**
 * @class BookForm BookForm.h
 *
 * @brief This class is a form containing all books fields.
 */
class BookForm : public QWidget, protected Ui::BookForm
{
	Q_OBJECT

	public:
		BookForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();
		void populatePublishersListWidget();
		void populateAuthorsListWidget();
		void populateTranslatorListWidget();

	protected slots:
		virtual void save() = 0;
		void coverFileChooser();
		void ebookFileChooser();

	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		QList<Publisher> getSelectedPublishers();
		QList<Author> getSelectedAuthors();
		Author getSelectedTranslator();
		Collection *c;
		QList<Theme> themeList;
		QList<Publisher> publisherList;
		QList<Author> authorList;

	signals:
		void closeRequested();
} ;

#endif //BOOKFORM_H
