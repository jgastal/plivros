/**
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "SearchForm.h"
#include "AddTheme.h"
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
	connect(publisherSearch, SIGNAL(clicked()), this, SLOT(createSearchPublisherForm()));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

///@brief Adds a tab and creates a form to add a theme in it.
void MainWindow::createAddThemeForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddTheme *at = new AddTheme(c, tabWidget);
	connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(at, tr("Add Theme"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

MainWindow::~MainWindow()
{
	delete c;
}

///@brief Adds a tab and creates a form to add a publisher in it.
void MainWindow::createAddPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddPublisher *ap = new AddPublisher(c, tabWidget);
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	connect(ap, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(ap, tr("Add Publisher"));	
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void MainWindow::createSearchPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(PropertiesGroupBox::publisher, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(sf, tr("Search Publisher"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

///@brief Closes a tab by deleting widget on position \a index of tabWidget.
void MainWindow::closeTab(int index)
{
	delete tabWidget->widget(index);
}

///@brief Closes a tab by deleting the sender.
void MainWindow::closeTab()
{
	delete sender();
}
