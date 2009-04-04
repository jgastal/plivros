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
	b.setRating(ratingWidget->getValue());
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
