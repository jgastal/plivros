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
 * @file EditTheme.cpp
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "ThemeForm.h"
#include "EditTheme.h"

#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

EditTheme::EditTheme(Collection *c, Theme t, QWidget *parent) : ThemeForm(c, parent)
{
	this->t = t;
	nameLineEdit->setText(t.getName());
	descriptionLineEdit->setText(t.getDescription());
}

///@brief Updates the theme described in the form(if validated).
void EditTheme::save()
{
	if(!validateInput())
		return;
	t.setName(nameLineEdit->text());
	t.setDescription(descriptionLineEdit->text());
	try
	{
		c->updateTheme(t);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your theme has not been added."));
		q.exec();
	}
	emit closeRequested();
}
