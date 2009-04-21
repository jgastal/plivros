/**
 * @file SearchForm.cpp
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include "SearchForm.h"

#include <QMessageBox>

#include "PropertiesGroupBox.h"
#include "MessageBoxDataBaseException.h"
#include "Section.h"

#include "Collection.h"
#include "DataBaseException.h"

#include "Data.h"

SearchForm::SearchForm(Section::section t, Collection *c, QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	propertiesGroupBox->init(t);
	this->c = c;
	this->t = t;
	connect(closePushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(searchPushButton, SIGNAL(clicked()), this, SLOT(search()));

	connect(tableWidget, SIGNAL(edit(DataObject*)), this, SIGNAL(edit(DataObject*)));
	connect(tableWidget, SIGNAL(del(DataObject*)), this, SIGNAL(del(DataObject*)));
	connect(tableWidget, SIGNAL(view(DataObject*)), this, SIGNAL(view(DataObject*)));
}

Section::section SearchForm::getType() const
{
	return t;
}

void SearchForm::search()
{
	unsigned short int prop;
	try
	{
		prop = propertiesGroupBox->getSelectedRadioButton();
	}
	catch(std::out_of_range ofr)
	{
		QMessageBox mb(this);
		mb.setIcon(QMessageBox::Warning);
		mb.setWindowTitle(tr("Warning"));
		mb.setText(tr("You must select a property in which to search."));
		mb.setStandardButtons(QMessageBox::Ok);
		mb.exec();
		return;
	}
	try
	{
		if(t == Section::Book)
		{
			QList<Book> bList = c->searchBooks(Book::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(bList);
		}
		else if(t == Section::Author)
		{
			QList<Author> aList = c->searchAuthors(Author::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(aList);
		}
		else if(t == Section::Publisher)
		{
			QList<Publisher> pList = c->searchPublishers(Publisher::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(pList);
		}
		else if(t == Section::Theme)
		{
			QList<Theme> tList = c->searchThemes(Theme::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(tList);
		}
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException mbdbe(&dbe, this);
		mbdbe.appendText("Unable to perform requested search.");
		mbdbe.exec();
	}
}
