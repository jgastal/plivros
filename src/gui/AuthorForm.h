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
 * @file AuthorForm.h
 *
 * @date 21/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef AUTHORFORM_H
#define AUTHORFORM_H

#include "ui_AuthorForm.h"

#include "Author.h"

class Collection;

/**
 * @class AuthorForm AuthorForm.h
 *
 * @brief This class is a form containing all authors fields.
 */
class AuthorForm : public QWidget, protected Ui::AuthorForm
{
	Q_OBJECT

	public:
		AuthorForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();
		
	protected slots:
		virtual void save() = 0;
		void picFileChooser();
		
	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		Collection *c;
		QList<Theme> themeList;
		
	signals:
		void closeRequested();
} ;

#endif //AUTHORFORM_H
