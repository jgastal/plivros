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
 * @file EditAuthor.h
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITAUTHOR_H
#define EDITAUTHOR_H

#include "AuthorForm.h"

#include "Author.h"
#include "Theme.h"

class Collection;

/**
 * @class EditAuthor EditAuthor.h
 *
 * @brief This widget is a form to add a author.
 */
class EditAuthor : public AuthorForm
{
	Q_OBJECT

	public:
		EditAuthor(Collection *c, Author p, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Author a;
		void setSelectedThemes(QList<Theme> tList);
} ;

#endif //EDITAUTHOR_H
