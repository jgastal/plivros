#include "ui_OperationsWidget.h"

#include "OperationsWidget.h"

#include "SearchForm.h"
#include "AddTheme.h"
#include "AddPublisher.h"
#include "AddAuthor.h"
#include "AddBook.h"

#include "Collection.h"

OperationsWidget::OperationsWidget(Collection *c, section s, QWidget *parent) : QWidget(parent)
{
	this->c = c;
	setupUi(this);
	setType(s);
}

void OperationsWidget::setType(section s)
{
	type = s;

	addLabel->disconnect();
	editLabel->disconnect();
	eraseLabel->disconnect();
	connect(addLabel, SIGNAL(linkActivated(QString)), this, SLOT(add()));
	connect(editLabel, SIGNAL(linkActivated(QString)), this, SLOT(edit()));
	connect(eraseLabel, SIGNAL(linkActivated(QString)), this, SLOT(erase()));
}

void OperationsWidget::add()
{
}

void OperationsWidget::edit()
{
}

void OperationsWidget::erase()
{
}

///@brief Adds a tab and creates a form to add a theme in it.
void OperationsWidget::createAddThemeForm()
{
	//set parent!
	AddTheme *at = new AddTheme(c);
	//connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
	
}

void OperationsWidget::createSearchThemeForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::theme, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

///@brief Adds a tab and creates a form to add a publisher in it.
void OperationsWidget::createAddPublisherForm()
{
	//set parent!
	AddPublisher *ap = new AddPublisher(c);
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	//connect(ap, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void OperationsWidget::createSearchPublisherForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::publisher, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void OperationsWidget::createAddAuthorForm()
{
	//set parent!
	AddAuthor *aa = new AddAuthor(c);
	connect(c, SIGNAL(themesChanged()), aa, SLOT(populateThemesListWidget()));
	//connect(aa, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void OperationsWidget::createSearchAuthorForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::author, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void OperationsWidget::createAddBookForm()
{
	//set parent!
	AddBook *ab = new AddBook(c);
	connect(c, SIGNAL(themesChanged()), ab, SLOT(populateThemesListWidget()));
	//connect(ab, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}

void OperationsWidget::createSearchBookForm()
{
	//set parent!
	SearchForm *sf = new SearchForm(PropertiesGroupBox::book, c);
	//connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	//Add somewhere
}