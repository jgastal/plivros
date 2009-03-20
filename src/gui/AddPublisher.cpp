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
		q.appendText(tr("Your publisher has not been added."));
		q.exec();
	}
	emit closeRequested();
}
