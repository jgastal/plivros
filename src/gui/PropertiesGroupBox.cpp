/**
 * @file PropertiesGroupBox.cpp
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#include "PropertiesGroupBox.h"

#include "Book.h"
#include "Theme.h"
#include "Author.h"
#include "Theme.h"

PropertiesGroupBox::PropertiesGroupBox(QWidget *parent) : QGroupBox(parent)
{
	grid.setParent(this);
	setLayout(&grid);
}

unsigned short int PropertiesGroupBox::getSelectedRadioButton()
{
	unsigned short int ret = 1;
	for(QList<QRadioButton*>::iterator it = radButtons.begin(); it != radButtons.end(); it++)
	{
		if((*it)->isChecked())
			return ret;
		ret++;
	}
	return 0;
		
}

void PropertiesGroupBox::init(type t)
{
	QStringList props;
	if(t == book)
	{
		setTitle("Book Properties");
		props = Book::getHeaders();
	}
	else if(t == author)
	{
		setTitle("Author Properties");
		props = Author::getHeaders();
	}
	if(t == publisher)
	{
		setTitle("Publisher Properties");
		props = Publisher::getHeaders();
	}
	if(t == theme)
	{
		setTitle("Theme Properties");
		props = Theme::getHeaders();
	}

	//Creates radio buttons
	for(QStringList::iterator it = props.begin(); it != props.end(); it++)
	{
		QRadioButton *rad = new QRadioButton(*it, this);
		radButtons.append(rad);
		grid.addWidget(rad);
	}
}