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
 * @file AddPublisher.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "AddPublisher.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Publisher.h"
#include "Theme.h"

AddPublisher::AddPublisher(Collection *c, QWidget *parent) : PublisherForm(c, parent)
{
	//just calling the parents constructor suffices
}

///@brief Adds publisher described in the form.
void AddPublisher::save()
{
	if(!validateInput())
		return;
	Publisher p;
	p.setName(nameLineEdit->text());
	p.setDescription(descriptionLineEdit->text());
	p.setCritique(critiqueLineEdit->text());
	p.setLogo(logoLineEdit->text());

	p.setThemes(getSelectedThemes());

	try
	{
		c->insertPublisher(p);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("The publisher has not been added."));
		q.exec();
	}
	emit closeRequested();
}
