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
 * @file EditTheme.h
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITTHEME_H
#define EDITTHEME_H

#include "ThemeForm.h"

#include "Theme.h"

class Collection;

/**
 * @class EditTheme EditTheme.h
 *
 * @brief This widget is a form to edit a theme.
 */
class EditTheme : public ThemeForm
{
	Q_OBJECT

	public:
		EditTheme(Collection *c, Theme t, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Theme t;
} ;

#endif //ADDTHEME_H
