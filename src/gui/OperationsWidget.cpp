/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ui_OperationsWidget.h"

#include "OperationsWidget.h"

#include "SearchForm.h"
#include "AddTheme.h"
#include "EditTheme.h"
#include "AddPublisher.h"
#include "EditPublisher.h"
#include "PublisherDetails.h"
#include "AddAuthor.h"
#include "EditAuthor.h"
#include "AuthorDetails.h"
#include "AddBook.h"
#include "EditBook.h"
#include "BookDetails.h"

#include "Collection.h"
#include "Data.h"

static const QString SS = "QWidget#%1 { background-color: %2; }";
static const QString THEMEBGCOLOR = "rgb(102, 67, 100)";
static const QString THEMEBTCOLOR = "rgb(125, 90, 193)";
static const QString PUBLISHERBGCOLOR = "rgb(122, 28, 45)";
static const QString PUBLISHERBTCOLOR = "rgb(171, 51, 61)";
static const QString AUTHORBGCOLOR = "rgb(63, 90, 111)";
static const QString AUTHORBTCOLOR = "rgb(140, 173, 223)";
static const QString BOOKBGCOLOR = "rgb(98, 115, 96)";
static const QString BOOKBTCOLOR = "rgb(115, 138, 115)";

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

	bTab = aTab = pTab = tTab = 0;
	bPix = aPix = pPix = tPix = 0;

	setSection(s);
	setSectionButton();
}

OperationsWidget::~OperationsWidget()
{
	delete bPix;
	delete aPix;
	delete pPix;
	delete tPix;
}

void OperationsWidget::setSection(Section::section s)
{
	section = s;
	if(bTab)
		bTab->hide();
	if(aTab)
		aTab->hide();
	if(pTab)
		pTab->hide();
	if(tTab)
		tTab->hide();

	//Making all buttons apear unselected, later on apropriate one will have apearance changed
	bookToolButton->setStyleSheet("");
	authorToolButton->setStyleSheet("");
	publisherToolButton->setStyleSheet("");
	themeToolButton->setStyleSheet("");

	QLayout *layout = formFrame->layout();
	if(section == Section::Book)
	{
		if(!bTab)
		{
			bTab = new QTabWidget(formFrame);
			bTab->setTabsClosable(true);
			connect(bTab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
			layout->addWidget(bTab);
			bPix = new QPixmap(":/bgs/big_books2.jpeg");
		}
		pictureLabel->setPixmap(*bPix);
		formFrame->setStyleSheet(SS.arg(formFrame->objectName()).arg(BOOKBGCOLOR));
		bookToolButton->setStyleSheet(SS.arg(bookToolButton->objectName()).arg(BOOKBTCOLOR));
		bTab->setVisible(true);
		if(!bTab->count())
			add();
	}
	else if(section == Section::Author)
	{
		if(!aTab)
		{
			aTab = new QTabWidget(formFrame);
			aTab->setTabsClosable(true);
			connect(aTab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
			layout->addWidget(aTab);
			aPix = new QPixmap(":/bgs/big_authors.jpeg");
		}
		pictureLabel->setPixmap(*aPix);
		formFrame->setStyleSheet(SS.arg(formFrame->objectName()).arg(AUTHORBGCOLOR));
		authorToolButton->setStyleSheet(SS.arg(authorToolButton->objectName()).arg(AUTHORBTCOLOR));
		aTab->setVisible(true);
		if(!aTab->count())
			add();
	}
	else if(section == Section::Publisher)
	{
		if(!pTab)
		{
			pTab = new QTabWidget(formFrame);
			pTab->setTabsClosable(true);
			connect(pTab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
			layout->addWidget(pTab);
			pPix = new QPixmap(":/bgs/big_publishers.jpeg");
		}
		pictureLabel->setPixmap(*pPix);
		pTab->setVisible(true);
		formFrame->setStyleSheet(SS.arg(formFrame->objectName()).arg(PUBLISHERBGCOLOR));
		publisherToolButton->setStyleSheet(SS.arg(publisherToolButton->objectName()).arg(PUBLISHERBTCOLOR));
		if(!pTab->count())
			add();
	}
	else if(section == Section::Theme)
	{
		if(!tTab)
		{
			tTab = new QTabWidget(formFrame);
			tTab->setTabsClosable(true);
			connect(tTab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
			layout->addWidget(tTab);
			tPix = new QPixmap(":/bgs/big_themes2.jpeg");
		}
		pictureLabel->setPixmap(*tPix);
		formFrame->setStyleSheet(SS.arg(formFrame->objectName()).arg(THEMEBGCOLOR));
		themeToolButton->setStyleSheet(SS.arg(themeToolButton->objectName()).arg(THEMEBTCOLOR));
		tTab->setVisible(true);
		if(!tTab->count())
			add();
	}
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

void OperationsWidget::edit(int id)
{
	Section::section s = ((SearchForm*)sender())->getType();
	if(s == Section::Book)
		createEditBookForm(id);
	else if(s == Section::Author)
		createEditAuthorForm(id);
	else if(s == Section::Publisher)
		createEditPublisherForm(id);
	else if(s == Section::Theme)
		createEditThemeForm(id);
}

void OperationsWidget::erase(int id)
{
	Section::section s = ((SearchForm*)sender())->getType();
	if(s == Section::Book)
		c->deleteBook(id);
	else if(s == Section::Author)
		c->deleteAuthor(id);
	else if(s == Section::Publisher)
		c->deletePublisher(id);
	else if(s == Section::Theme)
		c->deleteTheme(id);
}

void OperationsWidget::view(int id)
{
	Section::section s = ((SearchForm*)sender())->getType();
	if(s == Section::Book)
		createViewBookDetails(id);
	else if(s == Section::Author)
		createViewAuthorDetails(id);
	else if(s == Section::Publisher)
		createViewPublisherDetails(id);
}

void OperationsWidget::search()
{
	SearchForm *sf = new SearchForm(section, c);
	connect(sf, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	connect(sf, SIGNAL(edit(int)), this, SLOT(edit(int)));
	connect(sf, SIGNAL(del(int)), this, SLOT(erase(int)));
	connect(sf, SIGNAL(view(int)), this, SLOT(view(int)));

	int pos;
	if(section == Section::Book)
	{
		sf->setParent(bTab);
		connect(c, SIGNAL(booksChanged()), sf, SLOT(search()));
		pos = bTab->addTab(sf, tr("Search Books"));
		bTab->setCurrentIndex(pos);
	}
	else if(section == Section::Author)
	{
		sf->setParent(aTab);
		connect(c, SIGNAL(authorsChanged()), sf, SLOT(search()));
		pos = aTab->addTab(sf, tr("Search Authors"));
		aTab->setCurrentIndex(pos);
	}
	else if(section == Section::Publisher)
	{
		sf->setParent(pTab);
		connect(c, SIGNAL(publishersChanged()), sf, SLOT(search()));
		pos = pTab->addTab(sf, tr("Search Publishers"));
		pTab->setCurrentIndex(pos);
	}
	else if(section == Section::Theme)
	{
		sf->setParent(tTab);
		connect(c, SIGNAL(themesChanged()), sf, SLOT(search()));
		pos = tTab->addTab(sf, tr("Search Themes"));
		tTab->setCurrentIndex(pos);
	}
}

void OperationsWidget::searchBook(unsigned short int idx, QString str)
{
	search();
	SearchForm *sf = (SearchForm*)bTab->currentWidget();
	sf->search(idx, str);
}

///@brief Adds a tab and creates a form to add a theme in it.
void OperationsWidget::createAddThemeForm()
{
	tTab->setUpdatesEnabled(false);
	AddTheme *at = new AddTheme(c, tTab);
	connect(at, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tTab->addTab(at, tr("Add Theme"));
	tTab->setCurrentIndex(pos);
	tTab->setUpdatesEnabled(true);
}

void OperationsWidget::createEditThemeForm(int id)
{
	tTab->setUpdatesEnabled(false);
	EditTheme *et = new EditTheme(c, id, tTab);
	connect(et, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = tTab->addTab(et, tr("Edit Theme"));
	tTab->setCurrentIndex(pos);
	tTab->setUpdatesEnabled(true);
}

///@brief Adds a tab and creates a form to add a publisher in it.
void OperationsWidget::createAddPublisherForm()
{
	pTab->setUpdatesEnabled(false);
	AddPublisher *ap = new AddPublisher(c, pTab);
	connect(c, SIGNAL(themesChanged()), ap, SLOT(populateThemesListWidget()));
	connect(ap, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = pTab->addTab(ap, tr("Add Publisher"));
	pTab->setCurrentIndex(pos);
	pTab->setUpdatesEnabled(true);
}

void OperationsWidget::createEditPublisherForm(int id)
{
	pTab->setUpdatesEnabled(false);
	EditPublisher *ep = new EditPublisher(c, id, pTab);
	connect(c, SIGNAL(themesChanged()), ep, SLOT(populateThemesListWidget()));
	connect(ep, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = pTab->addTab(ep, tr("Edit Publisher"));
	pTab->setCurrentIndex(pos);
	pTab->setUpdatesEnabled(true);
}

void OperationsWidget::createViewPublisherDetails(int id)
{
	Publisher p = c->getPublisher(id);
	pTab->setUpdatesEnabled(false);
	PublisherDetails *pd = new PublisherDetails(p, pTab);

	int pos = pTab->addTab(pd, p.getName());
	pTab->setCurrentIndex(pos);
	pTab->setUpdatesEnabled(true);
}

void OperationsWidget::createAddAuthorForm()
{
	aTab->setUpdatesEnabled(false);
	AddAuthor *aa = new AddAuthor(c, aTab);
	connect(c, SIGNAL(themesChanged()), aa, SLOT(populateThemesListWidget()));
	connect(aa, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = aTab->addTab(aa, tr("Add Author"));
	aTab->setCurrentIndex(pos);
	aTab->setUpdatesEnabled(true);
}

void OperationsWidget::createEditAuthorForm(int id)
{
	aTab->setUpdatesEnabled(false);
	EditAuthor *ea = new EditAuthor(c, id, aTab);
	connect(c, SIGNAL(themesChanged()), ea, SLOT(populateThemesListWidget()));
	connect(ea, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = aTab->addTab(ea, tr("Edit Author"));
	aTab->setCurrentIndex(pos);
	aTab->setUpdatesEnabled(true);
}

void OperationsWidget::createViewAuthorDetails(int id)
{
	Author a = c->getAuthor(id);
	aTab->setUpdatesEnabled(false);
	AuthorDetails *ad = new AuthorDetails(a, aTab);
	int pos = aTab->addTab(ad, a.getName());
	aTab->setCurrentIndex(pos);
	aTab->setUpdatesEnabled(true);
}

void OperationsWidget::createAddBookForm()
{
	bTab->setUpdatesEnabled(false);
	AddBook *ab = new AddBook(c, bTab);
	connect(c, SIGNAL(themesChanged()), ab, SLOT(populateThemesListWidget()));
	connect(c, SIGNAL(publishersChanged()), ab, SLOT(populatePublishersListWidget()));
	connect(c, SIGNAL(authorsChanged()), ab, SLOT(populateAuthorsListWidget()));
	connect(c, SIGNAL(authorsChanged()), ab, SLOT(populateTranslatorListWidget()));
	connect(ab, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = bTab->addTab(ab, tr("Add Book"));
	bTab->setCurrentIndex(pos);
	bTab->setUpdatesEnabled(true);
}

void OperationsWidget::createEditBookForm(int id)
{
	bTab->setUpdatesEnabled(false);
	EditBook *eb = new EditBook(c, id, bTab);
	connect(c, SIGNAL(themesChanged()), eb, SLOT(populateThemesListWidget()));
	connect(c, SIGNAL(publishersChanged()), eb, SLOT(populatePublishersListWidget()));
	connect(c, SIGNAL(authorsChanged()), eb, SLOT(populateAuthorsListWidget()));
	connect(c, SIGNAL(authorsChanged()), eb, SLOT(populateTranslatorListWidget()));
	connect(eb, SIGNAL(closeRequested()), this, SLOT(closeTab()));
	int pos = bTab->addTab(eb, tr("Edit Book"));
	bTab->setCurrentIndex(pos);
	bTab->setUpdatesEnabled(true);
}

void OperationsWidget::createViewBookDetails(int id)
{
	Book b = c->getBook(id);
	bTab->setUpdatesEnabled(false);
	BookDetails *bd = new BookDetails(b, bTab);
	connect(bd, SIGNAL(authorClicked(QString)), this, SLOT(viewAuthor(QString)));
	connect(bd, SIGNAL(publisherClicked(QString)), this, SLOT(viewPublisher(QString)));
	int pos = bTab->addTab(bd, b.getTitle());
	bTab->setCurrentIndex(pos);
	bTab->setUpdatesEnabled(true);
}

void OperationsWidget::closeTab()
{
	delete sender();
}

void OperationsWidget::closeTab(int index)
{
	if(section == Section::Book)
		delete bTab->widget(index);
	else if(section == Section::Author)
		delete aTab->widget(index);
	else if(section == Section::Publisher)
		delete pTab->widget(index);
	else if(section == Section::Theme)
		delete tTab->widget(index);
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

void OperationsWidget::viewAuthor(QString url)
{
	if(!url.startsWith("view://"))
		return;
	url.replace("view://", "");
	createViewAuthorDetails(url.toInt());
}

void OperationsWidget::viewPublisher(QString url)
{
	if(!url.startsWith("view://"))
		return;
	url.replace("view://", "");
	createViewPublisherDetails(url.toInt());
}
