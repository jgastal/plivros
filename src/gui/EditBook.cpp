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
 * @file EditBook.cpp
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "EditBook.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Book.h"
#include "Publisher.h"
#include "Author.h"
#include "Theme.h"

EditBook::EditBook(Collection *c, Book b, QWidget *parent) : BookForm(c, parent)
{
	this->b = b;
	isbnLineEdit->setText(b.getIsbn());
	titleLineEdit->setText(b.getTitle());
	editionLineEdit->setText(QString::number(b.getEdition()));
	descriptionLineEdit->setText(b.getDescription());
	critiqueLineEdit->setText(b.getCritique());
	coverLineEdit->setText(b.getCover());
	ratingWidget->setRating(b.getRating());
	ebookLineEdit->setText(b.getEbook());
	pubDateEdit->setDate(b.getPubDate());
	udcLineEdit->setText(b.getUDC());
	setSelectedAuthors(b.getAuthors());
	setSelectedTranslator(b.getTranslator());
	setSelectedPublishers(b.getPublishers());
	setSelectedThemes(b.getThemes());
}

///@brief Adds author described in the form.
void EditBook::save()
{
	if(!validateInput())
		return;
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
		c->updateBook(b);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your book has not been added."));
		q.exec();
	}
	emit closeRequested();
}

void EditBook::setSelectedThemes(QList<Theme> tList)
{
	int i = 0;
	for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
	{
		if(tList.contains(*it))
			themesListWidget->item(i)->setSelected(true);
		i++;
	}
}

void EditBook::setSelectedPublishers(QList<Publisher> pList)
{
	int i = 0;
	for(QList<Publisher>::iterator it = publisherList.begin(); it != publisherList.end(); it++)
	{
		if(pList.contains(*it))
			publishersListWidget->item(i)->setSelected(true);
		i++;
	}
}

void EditBook::setSelectedAuthors(QList<Author> aList)
{
	int i = 0;
	for(QList<Author>::iterator it = authorList.begin(); it != authorList.end(); it++)
	{
		if(aList.contains(*it))
			authorsListWidget->item(i)->setSelected(true);
		i++;
	}
}

void EditBook::setSelectedTranslator(Author a)
{
	int index = authorList.indexOf(a);
	translatorComboBox->setCurrentIndex(index);
}
