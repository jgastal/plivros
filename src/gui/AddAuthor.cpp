/**
 * @file AddAuthor.cpp
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "AddAuthor.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Author.h"
#include "Theme.h"

AddAuthor::AddAuthor(Collection *c, QWidget *parent) : AuthorForm(c, parent)
{
	//just calling the parents constructor suffices
}

///@brief Adds author described in the form.
void AddAuthor::save()
{
	if(!validateInput())
		return;
	Author a;
	a.setFirstName(firstNameLineEdit->text());
	a.setLastName(lastNameLineEdit->text());
	a.setDescription(descriptionLineEdit->text());
	a.setCritique(critiqueLineEdit->text());
	a.setPicture(pictureLineEdit->text());
	a.setRating(ratingWidget->getValue());

	a.setThemes(getSelectedThemes());

	try
	{
		c->insertAuthor(a);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your author has not been added."));
		q.exec();
	}
	emit closeRequested();
}
