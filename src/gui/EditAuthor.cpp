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

EditAuthor::EditAuthor(Collection *c, Author a, QWidget *parent) : AuthorForm(c, parent)
{
	this->a = a;
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