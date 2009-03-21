/**
 * @file PropertiesGroupBox.cpp
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#include "PropertiesGroupBox.h"

#include <exception>
#include <stdexcept>

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
	unsigned short int ret = 0;
	for(QList<QRadioButton*>::iterator it = radButtons.begin(); it != radButtons.end(); it++)
	{
		if((*it)->isChecked())
			return ret;
		ret++;
	}
	throw std::out_of_range("No radio button selected.");
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
	else if(t == publisher)
	{
		setTitle("Publisher Properties");
		props = Publisher::getHeaders();
	}
	else if(t == theme)
	{
		setTitle("Theme Properties");
		props = Theme::getHeaders();
	}

	//Creates radio buttons
	radButtons.clear();
	int row = 0, col = 0;
	for(QStringList::iterator it = props.begin(); it != props.end(); it++)
	{
		QRadioButton *rad = new QRadioButton(*it, this);
		radButtons.append(rad);
		grid.addWidget(rad, row, col++);
		if(col > 5)
		{
			col = 0;
			row++;
		}
		
	}
}