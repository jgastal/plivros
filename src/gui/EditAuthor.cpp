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
 * @file EditAuthor.cpp
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "EditAuthor.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Author.h"
#include "Theme.h"

EditAuthor::EditAuthor(Collection *c, int id, QWidget *parent) : AuthorForm(c, parent)
{
	a = c->getAuthor(id);
	firstNameLineEdit->setText(a.getFirstName());
	lastNameLineEdit->setText(a.getLastName());
	descriptionLineEdit->setText(a.getDescription());
	critiqueLineEdit->setText(a.getCritique());
	pictureLineEdit->setText(a.getPicture());
	ratingWidget->setRating(a.getRating());
	setSelectedThemes(a.getThemes());
}

///@brief Adds author described in the form.
void EditAuthor::save()
{
	if(!validateInput())
		return;
	a.setFirstName(firstNameLineEdit->text());
	a.setLastName(lastNameLineEdit->text());
	a.setDescription(descriptionLineEdit->text());
	a.setCritique(critiqueLineEdit->text());
	a.setPicture(pictureLineEdit->text());
	a.setRating(ratingWidget->getRating());

	a.setThemes(getSelectedThemes());

	try
	{
		c->updateAuthor(a);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your author has not been added."));
		q.exec();
	}
	emit closeRequested();
}

void EditAuthor::setSelectedThemes(QList<Theme> tList)
{
	int i = 0;
	for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
	{
		if(tList.contains(*it))
			themesListWidget->item(i)->setSelected(true);
		i++;
	}
}
