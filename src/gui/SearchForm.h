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
 * @file SearchForm.h
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include "ui_SearchForm.h"

#include "Section.h"

#include <QWidget>

class Collection;
class DataObject;

class SearchForm : public QWidget, private Ui::SearchForm
{
	Q_OBJECT

	public:
		SearchForm(Section::section t, Collection *c, QWidget *parent = 0);
		Section::section getType() const;

	public slots:
		void search();
		void search(unsigned short int where, QString what);

	signals:
		void closeRequested();
		void edit(int);
		void del(int);
		void view(int);

	private:
		Collection *c;
		Section::section t;
} ;

#endif //SEARCHFORM_H
