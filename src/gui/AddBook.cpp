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
 * @file AddBook.cpp
 *
 * @date 23/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "AddBook.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Book.h"

AddBook::AddBook(Collection *c, QWidget *parent) : BookForm(c, parent)
{
	pubDateEdit->setDate(QDate::currentDate());
	//just calling the parents constructor suffices
}

///@brief Adds book described in the form.
void AddBook::save()
{
	if(!validateInput())
		return;
	Book b;
	b.setIsbn(isbnLineEdit->text().toStdString().c_str());
	b.setTitle(titleLineEdit->text());
	b.setEdition(editionLineEdit->text().toInt());
	b.setCritique(critiqueLineEdit->text());
	b.setDescription(descriptionLineEdit->text());
	b.setRating(ratingWidget->getRating());
	b.setCover(coverLineEdit->text());
	b.setEbook(ebookLineEdit->text());
	b.setPubDate(pubDateEdit->date());
	b.setUDC(udcLineEdit->text());

	b.setThemes(getSelectedThemes());
	b.setPublishers(getSelectedPublishers());
	b.setAuthors(getSelectedAuthors());
	b.setTranslator(getSelectedTranslator());

	try
	{
		c->insertBook(b);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("The book has not been added."));
		q.exec();
	}
	emit closeRequested();
}
