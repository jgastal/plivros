/**
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

/**
 * TODO: Remove code that no longer makes sense.
 * TODO: Text over images on hover.
 * TODO: Figure out system user name.
 * TODO: Should displayWidget be separated from MainWindow?
 * TODO: searchLabel above searchLineEdit?
 */

#include "SearchForm.h"
#include "AddTheme.h"
#include "AddPublisher.h"
#include "AddAuthor.h"
#include "AddBook.h"

#include "MainWindow.h"

#include "Collection.h"

///@brief Constructor. Creates a collection, setups the gui and connects slots and signals.
MainWindow::MainWindow(QString userName, QMainWindow *parent) : QMainWindow(parent)
{
	c = new Collection("User");
	setupUi(this);

	connect(quitLabel, SIGNAL(linkActivated(QString)), this, SLOT(close()));

	QString userStr = userLabel->text();
	userStr.replace("<user>", userName);
	userLabel->setText(userStr);

	connect(themeHoverPushButton, SIGNAL(hoverEnter()), this, SLOT(themeEnterHover()));
	connect(themeHoverPushButton, SIGNAL(hoverLeave()), this, SLOT(leaveHover()));
	connect(publisherHoverPushButton, SIGNAL(hoverEnter()), this, SLOT(publisherEnterHover()));
	connect(publisherHoverPushButton, SIGNAL(hoverLeave()), this, SLOT(leaveHover()));
	connect(authorHoverPushButton, SIGNAL(hoverEnter()), this, SLOT(authorEnterHover()));
	connect(authorHoverPushButton, SIGNAL(hoverLeave()), this, SLOT(leaveHover()));
	connect(bookHoverPushButton, SIGNAL(hoverEnter()), this, SLOT(bookEnterHover()));
	connect(bookHoverPushButton, SIGNAL(hoverLeave()), this, SLOT(leaveHover()));
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

void MainWindow::themeEnterHover()
{
	themeHoverPushButton->setText(tr("Themes"));
	QString ss = themeHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	themeHoverPushButton->setStyleSheet(ss);
	displayWidget->setStyleSheet("QWidget#displayWidget { background-image: url(:/imgs/imgs/Pages.jpg); }");
}

void MainWindow::publisherEnterHover()
{
	publisherHoverPushButton->setText(tr("Publishers"));
	QString ss = publisherHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	publisherHoverPushButton->setStyleSheet(ss);
	displayWidget->setStyleSheet("QWidget#displayWidget { background-image: url(:/imgs/imgs/Publisher.gif); }");
}

void MainWindow::authorEnterHover()
{
	authorHoverPushButton->setText(tr("Authors"));
	QString ss = authorHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	authorHoverPushButton->setStyleSheet(ss);
	displayWidget->setStyleSheet("QWidget#displayWidget { background-image: url(:/imgs/imgs/Author.gif); }");
}

void MainWindow::bookEnterHover()
{
	bookHoverPushButton->setText(tr("Books"));
	QString ss = bookHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	bookHoverPushButton->setStyleSheet(ss);
	displayWidget->setStyleSheet("QWidget#displayWidget { background-image: url(:/imgs/imgs/Book.gif); }");
}

void MainWindow::leaveHover()
{
	static_cast<HoverPushButton*>(sender())->setText("");
	QString ss = static_cast<HoverPushButton*>(sender())->styleSheet();
	ss.remove("\nfont: bold 20pt;");
	static_cast<HoverPushButton*>(sender())->setStyleSheet(ss);
	displayWidget->setStyleSheet("");
}
