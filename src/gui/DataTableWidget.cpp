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
 * @file DataTableWidget.cpp
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

#include "DataTableWidget.h"

DataTableWidget::DataTableWidget(QWidget *parent) : QTableWidget(parent)
{
	setEditTriggers(0);

	initActions();
	setContextMenuPolicy(Qt::ActionsContextMenu);
}

DataTableWidget::~DataTableWidget()
{
	for(int i = 0; i < curDataList.size(); i++)
		delete curDataList.at(i);
}

void DataTableWidget::populateTable(QList<Book> dataList)
{
	setColumnCount(Book::propertiesCount);
	setHorizontalHeaderLabels(Book::headers);
	loop(dataList);
	addAction(view_act);
}

void DataTableWidget::populateTable(QList<Author> dataList)
{
	setColumnCount(Author::propertiesCount);
	setHorizontalHeaderLabels(Author::headers);
	loop(dataList);
	addAction(view_act);
}

void DataTableWidget::populateTable(QList<Publisher> dataList)
{
	setColumnCount(Publisher::propertiesCount);
	setHorizontalHeaderLabels(Publisher::headers);
	loop(dataList);
	addAction(view_act);
}

void DataTableWidget::populateTable(QList<Theme> dataList)
{
	setColumnCount(Theme::propertiesCount);
	setHorizontalHeaderLabels(Theme::headers);
	loop(dataList);
}

void DataTableWidget::edit()
{
	if(curDataList.size())
		emit edit(curDataList.at(currentRow()));
}

void DataTableWidget::del()
{
	if(curDataList.size())
		emit del(curDataList.at(currentRow()));
}

void DataTableWidget::view()
{
	if(curDataList.size())
		emit view(curDataList.at(currentRow()));
}

template <class Type>
void DataTableWidget::loop(QList<Type> dataList)
{
	setRowCount(dataList.size());
	unsigned short int row = 0;
	for(typename QList<Type>::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		QStringList prop = it->getProperties();
		unsigned short int col = 0;
		for(QStringList::iterator p_it = prop.begin(); p_it != prop.end(); p_it++)
		{
			QTableWidgetItem *qtwi = new QTableWidgetItem(*p_it);
			setItem(row, col++, qtwi);
		}
		curDataList.append(new Type(*it));
		row++;
	}
}

void DataTableWidget::initActions()
{
	edit_act = new QAction(QIcon(":/icons/edit.png"), tr("Edit"), this);
	connect(edit_act, SIGNAL(triggered()), this, SLOT(edit()));
	del_act = new QAction(QIcon(":/icons/delete.png"), tr("Delete"), this);
	connect(del_act, SIGNAL(triggered()), this, SLOT(del()));
	view_act = new QAction(QIcon(":/icons/view_details.png"), tr("View details"), this);
	connect(view_act, SIGNAL(triggered()), this, SLOT(view()));

	addAction(edit_act);
	addAction(del_act);
}
