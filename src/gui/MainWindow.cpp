/**
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

/**
 * TODO: Remove code that no longer makes sense.
 * TODO: Figure out system user name.
 * TODO: searchLabel above searchLineEdit?
 */

#include "CategoryFrame.h"
#include "SearchForm.h"
#include "AddTheme.h"
#include "AddPublisher.h"
#include "AddAuthor.h"
#include "AddBook.h"

#include "MainWindow.h"

#include "Collection.h"

///@brief Constructor. Creates a collection, setups the gui and connects slots and signals.
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	c = new Collection("User");
	setupUi(this);

	connect(quitLabel, SIGNAL(linkActivated(QString)), this, SLOT(close()));

	cf = new CategoryFrame();
	displayWidget->layout()->addWidget(cf);
}

MainWindow::~MainWindow()
{
	delete c;
}

///@brief Adds a tab and creates a form to add a theme in it.
void MainWindow::createAddThemeForm()
{
	//set parent!
	AddTheme *at = new AddTheme(c);
	//connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere

}

void MainWindow::createSearchThemeForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::theme, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

///@brief Adds a tab and creates a form to add a publisher in it.
void MainWindow::createAddPublisherForm()
{
	//set parent!
	AddPublisher *ap = new AddPublisher(c);
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	//connect(ap, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void MainWindow::createSearchPublisherForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::publisher, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void MainWindow::createAddAuthorForm()
{
	//set parent!
	AddAuthor *aa = new AddAuthor(c);
	connect(c, SIGNAL(themesChanged()), aa, SLOT(populateThemesListWidget()));
	//connect(aa, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void MainWindow::createSearchAuthorForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::author, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void MainWindow::createAddBookForm()
{
	//set parent!
	AddBook *ab = new AddBook(c);
	connect(c, SIGNAL(themesChanged()), ab, SLOT(populateThemesListWidget()));
	//connect(ab, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void MainWindow::createSearchBookForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::book, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}
