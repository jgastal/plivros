#include "DataTableWidget.h"

DataTableWidget::DataTableWidget(QWidget *parent) : QTableWidget(parent)
{
	setEditTriggers(0);
	connect(this, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
		 this, SLOT(setCurItem(QTableWidgetItem*, QTableWidgetItem*)));
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

void DataTableWidget::setCurItem(QTableWidgetItem *oldItem, QTableWidgetItem *newItem)
{
	if(newItem)
		emit currentItemChanged(curDataList.at(newItem->row()));
	else
		emit currentItemChanged(NULL);
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