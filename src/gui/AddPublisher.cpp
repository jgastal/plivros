/**
 * @file AddPublisher.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>

#include "AddPublisher.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Publisher.h"
#include "Theme.h"

AddPublisher::AddPublisher(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	connect(addPushButton, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

///@brief Closes the tab that owns this form.
void AddPublisher::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

void AddPublisher::add()
{
	if(!validateInput())
		return;
	Publisher p;
	p.setName(nameLineEdit->text().toStdString());
	p.setDescription(descriptionLineEdit->text().toStdString());
	p.setCritique(critiqueLineEdit->text().toStdString());
	p.setLogo(logoLineEdit->text().toStdString());

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
	close();
}

bool AddPublisher::validateInput()
{
	return true;
}

QList<Theme> AddPublisher::getSelectedThemes()
{
	QList<Theme> list;
	for(int i = 0; i < themesListWidget->count(); i++)
	{
		if(themesListWidget->item(i)->isSelected())
			list.append(themeList.at(i));
	}
	return list;
}

void AddPublisher::populateThemesListWidget()
{
	try
	{
		themeList = c->searchThemes(Theme::t_name, "");
		QStringList strList;
		for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
			strList.append(it->getName().c_str());
		themesListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of themes.\nClosing this tab."));
		q.exec();
	}
}
