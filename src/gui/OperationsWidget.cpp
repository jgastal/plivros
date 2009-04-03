#include "ui_OperationsWidget.h"

#include "OperationsWidget.h"

#include "SearchForm.h"
#include "AddTheme.h"
#include "AddPublisher.h"
#include "AddAuthor.h"
#include "AddBook.h"

#include "Collection.h"

OperationsWidget::OperationsWidget(Collection *c, Section::section s, QWidget *parent) : QWidget(parent)
{
	this->c = c;
	setupUi(this);
	tabWidget->clear();
	setSection(s);
	add();
}

void OperationsWidget::setSection(Section::section s)
{
	section = s;
}

void OperationsWidget::add()
{
	if(section == Section::Book)
		createAddBookForm();
	else if(section == Section::Author)
		createAddAuthorForm();
	else if(section == Section::Publisher)
		createAddPublisherForm();
	else if(section == Section::Theme)
		createAddThemeForm();
}

void OperationsWidget::edit()
{
	/*if(section == Section::Book)
		createEditBookForm();
	else if(section == Section::Author)
		createEditAuthorForm();
	else if(section == Section::Publisher)
		createEditPublisherForm();
	else if(section == Section::Theme)
		createEditThemeForm();*/
}

void OperationsWidget::erase()
{
	/*if(section == Section::Book)
		eraseBook();
	else if(section == Section::Author)
		eraseAuthor();
	else if(section == Section::Publisher)
		erasePublisher();
	else if(section == Section::Theme)
		eraseTheme();*/
}

///@brief Adds a tab and creates a form to add a theme in it.
void OperationsWidget::createAddThemeForm()
{
	AddTheme *at = new AddTheme(c, tabWidget);
	connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
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