/**
 * @file EditPublisher.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>
#include <QFileDialog>

#include "EditPublisher.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Publisher.h"
#include "Theme.h"

EditPublisher::EditPublisher(Collection *c, Publisher p, QWidget *parent) : PublisherForm(c, parent)
{
	this->p = p;
	nameLineEdit->setText(p.getName());
	descriptionLineEdit->setText(p.getDescription());
	critiqueLineEdit->setText(p.getCritique());
	logoLineEdit->setText(p.getLogo());
	setSelectedThemes(p.getThemes());
}

///@brief Adds publisher described in the form.
void EditPublisher::save()
{
	if(!validateInput())
		return;
	p.setName(nameLineEdit->text());
	p.setDescription(descriptionLineEdit->text());
	p.setCritique(critiqueLineEdit->text());
	p.setLogo(logoLineEdit->text());

	p.setThemes(getSelectedThemes());

	try
	{
		c->updatePublisher(p);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Your publisher has not been added."));
		q.exec();
	}
	close();
}

void EditPublisher::setSelectedThemes(QList<Theme> tList)
{
	int i = 0;
	for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
	{
		if(tList.contains(*it))
			themesListWidget->item(i)->setSelected(true);
		i++;
	}
}