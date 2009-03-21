#include "SearchForm.h"

#include <QMessageBox>

#include "PropertiesGroupBox.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"

#include "Data.h"

SearchForm::SearchForm(PropertiesGroupBox::type t, Collection *c, QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	propertiesGroupBox->init(t);
	this->c = c;
	this->t = t;
	connect(closePushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(searchPushButton, SIGNAL(clicked()), this, SLOT(search()));
	connect(tableWidget, SIGNAL(currentItemChanged(DataObject*)), this, SIGNAL(currentItemChanged(DataObject*)));
}

PropertiesGroupBox::type SearchForm::getType() const
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
		if(t == PropertiesGroupBox::book)
		{
			QList<Book> bList = c->searchBooks(Book::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(bList);
		}
		else if(t == PropertiesGroupBox::author)
		{
			QList<Author> aList = c->searchAuthors(Author::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(aList);
		}
		else if(t == PropertiesGroupBox::publisher)
		{
			QList<Publisher> pList = c->searchPublishers(Publisher::getHeader(prop), searchLineEdit->text());
			tableWidget->populateTable(pList);
		}
		else if(t == PropertiesGroupBox::theme)
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
