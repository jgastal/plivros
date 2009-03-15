/**
 * @file AddPublisher.cpp
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QList>

#include "AddPublisher.h"

#include "Collection.h"
#include "Publisher.h"
#include "Theme.h"

AddPublisher::AddPublisher(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	try
	{
		themeList = c->searchThemes(Theme::t_name, "");
	}
	catch(DataBaseException dbe)
	{
		//handle erros
	}
	QStringList strList;
	for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
		strList.append(it->getName().c_str());
	setupUi(this);
	themesListWidget->insertItems(0, strList);
	//connect(addPushButton, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void AddPublisher::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}
