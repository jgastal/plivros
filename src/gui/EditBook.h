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
 * @file EditBook.h
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITBOOK_H
#define EDITBOOK_H

#include "BookForm.h"

#include "Book.h"
#include "Publisher.h"
#include "Author.h"
#include "Theme.h"

class Collection;

/**
 * @class EditBook EditBook.h
 *
 * @brief This widget is a form to add a book.
 */
class EditBook : public BookForm
{
	Q_OBJECT

	public:
		EditBook(Collection *c, int id, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Book b;
		void setSelectedThemes(QList<Theme> tList);
		void setSelectedAuthors(QList<Author> aList);
		void setSelectedTranslator(Author a);
		void setSelectedPublishers(QList<Publisher> pList);
} ;

#endif //EDITBOOK_H
