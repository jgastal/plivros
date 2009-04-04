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

void OperationsWidget::search()
{
	if(section == Section::Book)
		createSearchBookForm();
	else if(section == Section::Author)
		createSearchAuthorForm();
	else if(section == Section::Publisher)
		createSearchPublisherForm();
	else if(section == Section::Theme)
		createSearchThemeForm();
}

///@brief Adds a tab and creates a form to add a theme in it.
void OperationsWidget::createAddThemeForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddTheme *at = new AddTheme(c, tabWidget);
	connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(at, tr("Add Theme"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createSearchThemeForm()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(Section::Theme, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(sf, tr("Search Themes"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

///@brief Adds a tab and creates a form to add a publisher in it.
void OperationsWidget::createAddPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddPublisher *ap = new AddPublisher(c, tabWidget);
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	connect(ap, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(ap, tr("Add Publisher"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createSearchPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(Section::Publisher, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(sf, tr("Search Publishers"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createAddAuthorForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddAuthor *aa = new AddAuthor(c, tabWidget);
	connect(c, SIGNAL(themesChanged()), aa, SLOT(populateThemesListWidget()));
	connect(aa, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(aa, tr("Add Author"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createSearchAuthorForm()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(Section::Author, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(sf, tr("Search Authors"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createAddBookForm()
{
	tabWidget->setUpdatesEnabled(false);
	AddBook *ab = new AddBook(c, tabWidget);
	connect(c, SIGNAL(themesChanged()), ab, SLOT(populateThemesListWidget()));
	connect(c, SIGNAL(publishersChanged()), ab, SLOT(populatePublishersListWidget()));
	connect(c, SIGNAL(authorsChanged()), ab, SLOT(populateAuthorsListWidget()));
	connect(c, SIGNAL(authorsChanged()), ab, SLOT(populateTranslatorListWidget()));
	connect(ab, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(ab, tr("Add Book"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::createSearchBookForm()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(Section::Book, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(sf, tr("Search Books"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void OperationsWidget::closeTab()
{
	delete sender();
}

void OperationsWidget::closeTab(int index)
{
	delete tabWidget->widget(index);
}