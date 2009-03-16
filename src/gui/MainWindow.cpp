/**
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "AddTheme.h"
#include "EditTheme.h"
#include "AddPublisher.h"

#include "MainWindow.h"

#include "Collection.h"

///@brief Constructor. Creates a collection, setups the gui and connects slots and signals.
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	c = new Collection("User");
	setupUi(this);
	tabWidget->clear();
	connect(themesAdd, SIGNAL(clicked()), this, SLOT(createAddThemeForm()));
	connect(publisherAdd, SIGNAL(clicked()), this, SLOT(createAddPublisherForm()));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

///@brief Adds a tab and creates a form to add a theme in it.
void MainWindow::createAddThemeForm()
{
	tabWidget->setUpdatesEnabled(false);
	int pos = tabWidget->addTab(new AddTheme(c, tabWidget), tr("Add Theme"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

///@brief Adds a tab and creates a form to add a publisher in it.
void MainWindow::createAddPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddPublisher *ap = new AddPublisher(c, tabWidget);
	int pos = tabWidget->addTab(ap, tr("Add Publisher"));
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

///@brief Closes any given tab.
void MainWindow::closeTab(int index)
{
	tabWidget->removeTab(index);
}
