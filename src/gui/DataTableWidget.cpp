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

	edit_act = new QAction(QIcon(":/icons/edit.png"), tr("Edit"), this);
	connect(edit_act, SIGNAL(triggered()), this, SLOT(edit()));
	del_act = new QAction(QIcon(":/icons/delete.png"), tr("Delete"), this);
	connect(del_act, SIGNAL(triggered()), this, SLOT(del()));
	view_act = new QAction(QIcon(":/icons/view_details.png"), tr("View details"), this);
	connect(view_act, SIGNAL(triggered()), this, SLOT(view()));
}

void DataTableWidget::populateTable(QList<Book> dataList)
{
	setColumnCount(Book::propertiesCount);
	setHorizontalHeaderLabels(Book::headers);
	loop(dataList);
	
}

void DataTableWidget::populateTable(QList<Author> dataList)
{
	setColumnCount(Author::propertiesCount);
	setHorizontalHeaderLabels(Author::headers);
	loop(dataList);
}

void DataTableWidget::populateTable(QList<Publisher> dataList)
{
	setColumnCount(Publisher::propertiesCount);
	setHorizontalHeaderLabels(Publisher::headers);
	loop(dataList);
}

void DataTableWidget::populateTable(QList<Theme> dataList)
{
	setColumnCount(Theme::propertiesCount);
	setHorizontalHeaderLabels(Theme::headers);
	loop(dataList);
}

void DataTableWidget::edit()
{
	emit edit(curDataList.at(currentColumn()));
}

void DataTableWidget::del()
{
	emit del(curDataList.at(currentColumn()));
}

void DataTableWidget::view()
{
	emit view(curDataList.at(currentColumn()));
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
		curDataList.append(&(*it));
		row++;
	}
}

void DataTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(edit_act);
	menu.addAction(del_act);
	menu.addAction(view_act);
	menu.exec(event->globalPos());
}
