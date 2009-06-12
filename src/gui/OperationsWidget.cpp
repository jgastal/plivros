#include "ui_OperationsWidget.h"

#include "OperationsWidget.h"

#include "SearchForm.h"
#include "AddTheme.h"
#include "EditTheme.h"
#include "AddPublisher.h"
#include "EditPublisher.h"
#include "AddAuthor.h"
#include "EditAuthor.h"
#include "AddBook.h"
#include "EditBook.h"

#include "Collection.h"
#include "Data.h"

static QString bgss = "QWidget#%1 { "
"background: url(:bgs/%2);\n"
"background-repeat: no-repeat;\n"
"background-position: center center;\n}\n"
"QLabel { background: rgba(0, 0, 0, 0); }";

OperationsWidget::OperationsWidget(Collection *c, Section::section s, QWidget *parent) : QWidget(parent)
{
	this->c = c;
	setupUi(this);

	btGroup = new QButtonGroup(this);
	btGroup->addButton(themeToolButton);
	btGroup->addButton(publisherToolButton);
	btGroup->addButton(authorToolButton);
	btGroup->addButton(bookToolButton);
	connect(btGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setSection(QAbstractButton*)));

	bgss = bgss.arg(centralWidget->objectName());
	tabWidget->clear();
	setSection(s);
	setSectionButton();
}

void OperationsWidget::setSection(Section::section s)
{
	section = s;

	if(section == Section::Book)
		centralWidget->setStyleSheet(bgss.arg("big_books2.jpeg"));
	else if(section == Section::Author)
		centralWidget->setStyleSheet(bgss.arg("big_authors.jpeg"));
	else if(section == Section::Publisher)
		centralWidget->setStyleSheet(bgss.arg("big_publishers.jpeg"));
	else if(section == Section::Theme)
		centralWidget->setStyleSheet(bgss.arg("big_themes2.jpeg"));
	add();
}

void OperationsWidget::setSectionButton()
{
	if(section == Section::Book)
	{
		bookToolButton->blockSignals(true);
		bookToolButton->setChecked(true);
		bookToolButton->blockSignals(false);
	}
	else if(section == Section::Author)
	{
		authorToolButton->blockSignals(true);
		authorToolButton->setChecked(true);
		authorToolButton->blockSignals(false);
	}
	else if(section == Section::Publisher)
	{
		publisherToolButton->blockSignals(true);
		publisherToolButton->setChecked(true);
		publisherToolButton->blockSignals(false);
	}
	else if(section == Section::Theme)
	{
		themeToolButton->blockSignals(true);
		themeToolButton->setChecked(true);
		themeToolButton->blockSignals(false);
	}
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

void OperationsWidget::edit(DataObject *dobj)
{
	if(section == Section::Book)
		createEditBookForm((Book*)dobj);
	else if(section == Section::Author)
		createEditAuthorForm((Author*)dobj);
	else if(section == Section::Publisher)
		createEditPublisherForm((Publisher*)dobj);
	else if(section == Section::Theme)
		createEditThemeForm((Theme*)dobj);
}

void OperationsWidget::erase(DataObject *dobj)
{
	if(section == Section::Book)
		c->deleteBook(dobj->getId());
	else if(section == Section::Author)
		c->deleteAuthor(dobj->getId());
	else if(section == Section::Publisher)
		c->deletePublisher(dobj->getId());
	else if(section == Section::Theme)
		c->deleteTheme(dobj->getId());
}

void OperationsWidget::search()
{
	tabWidget->setUpdatesEnabled(false);
	SearchForm *sf = new SearchForm(section, c, tabWidget);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	connect(sf, SIGNAL(edit(DataObject*)), this, SLOT(edit(DataObject*)));
	connect(sf, SIGNAL(del(DataObject*)), this, SLOT(erase(DataObject*)));

	int pos;
	if(section == Section::Book)
	{
		connect(c, SIGNAL(booksChanged()), sf, SLOT(search()));
		pos = tabWidget->addTab(sf, tr("Search Books"));
	}
	else if(section == Section::Author)
	{
		connect(c, SIGNAL(authorsChanged()), sf, SLOT(search()));
		pos = tabWidget->addTab(sf, tr("Search Authors"));
	}
	else if(section == Section::Publisher)
	{
		connect(c, SIGNAL(publishersChanged()), sf, SLOT(search()));
		pos = tabWidget->addTab(sf, tr("Search Publishers"));
	}
	else if(section == Section::Theme)
	{
		connect(c, SIGNAL(themesChanged()), sf, SLOT(search()));
		pos = tabWidget->addTab(sf, tr("Search Themes"));
	}

	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
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

void OperationsWidget::createEditThemeForm(Theme *t)
{
	tabWidget->setUpdatesEnabled(false);
	EditTheme *et = new EditTheme(c, *t, tabWidget);
	connect(et, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(et, tr("Edit Theme"));
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

void OperationsWidget::createEditPublisherForm(Publisher *p)
{
	tabWidget->setUpdatesEnabled(false);
	EditPublisher *ep = new EditPublisher(c, *p, tabWidget);
	connect(c, SIGNAL(themesChanged()), ep, SLOT(populateThemesListWidget()));
	connect(ep, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(ep, tr("Edit Publisher"));
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

void OperationsWidget::createEditAuthorForm(Author *a)
{
	tabWidget->setUpdatesEnabled(false);
	EditAuthor *ea = new EditAuthor(c, *a, tabWidget);
	connect(c, SIGNAL(themesChanged()), ea, SLOT(populateThemesListWidget()));
	connect(ea, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(ea, tr("Edit Author"));
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

void OperationsWidget::createEditBookForm(Book *b)
{
	tabWidget->setUpdatesEnabled(false);
	EditBook *eb = new EditBook(c, *b, tabWidget);
	connect(c, SIGNAL(themesChanged()), eb, SLOT(populateThemesListWidget()));
	connect(c, SIGNAL(publishersChanged()), eb, SLOT(populatePublishersListWidget()));
	connect(c, SIGNAL(authorsChanged()), eb, SLOT(populateAuthorsListWidget()));
	connect(c, SIGNAL(authorsChanged()), eb, SLOT(populateTranslatorListWidget()));
	connect(eb, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tabWidget->addTab(eb, tr("Edit Book"));
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

void OperationsWidget::setSection(QAbstractButton *bt)
{
	if(bt == themeToolButton)
		setSection(Section::Theme);
	else if(bt == publisherToolButton)
		setSection(Section::Publisher);
	else if(bt == authorToolButton)
		setSection(Section::Author);
	else if(bt == bookToolButton)
		setSection(Section::Book);
}
