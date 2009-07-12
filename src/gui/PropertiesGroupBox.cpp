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
/**
 * @file PropertiesGroupBox.cpp
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#include "PropertiesGroupBox.h"

#include <stdexcept>

#include "Book.h"
#include "Theme.h"
#include "Author.h"
#include "Theme.h"

#include "Section.h"

PropertiesGroupBox::PropertiesGroupBox(QWidget *parent) : QGroupBox(parent)
{
	grid.setParent(this);
	setLayout(&grid);
}

unsigned short int PropertiesGroupBox::getSelectedRadioButton() throw(std::out_of_range)
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

void PropertiesGroupBox::setSelectedRadioButton(unsigned short int idx) throw(std::out_of_range)
{
	for(int i = 0; i < radButtons.size(); i++)
	{
		if(i == idx)
		{
			radButtons.at(i)->setChecked(true);
			return;
		}
	}
	throw std::out_of_range("No radio button selected.");
}

void PropertiesGroupBox::init(Section::section t)
{
	QStringList props;
	if(t == Section::Book)
	{
		setTitle(tr("Book Properties"));
		props = Book::getHeaders();
	}
	else if(t == Section::Author)
	{
		setTitle(tr("Author Properties"));
		props = Author::getHeaders();
	}
	else if(t == Section::Publisher)
	{
		setTitle(tr("Publisher Properties"));
		props = Publisher::getHeaders();
	}
	else if(t == Section::Theme)
	{
		setTitle(tr("Theme Properties"));
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