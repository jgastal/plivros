/**
 * @file DataTableWidget.h
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef DATATABLEWIDGET_H
#define DATATABLEWIDGET_H

#include <QTableWidget>

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

class DataObject;

class DataTableWidget : public QTableWidget
{
	Q_OBJECT

	public:
		DataTableWidget(QWidget *parent = 0);

	public slots:
		void populateTable(QList<Book> dataList);
		void populateTable(QList<Author> dataList);
		void populateTable(QList<Publisher> dataList);
		void populateTable(QList<Theme> dataList);

	private slots:
		void setCurItem(QTableWidgetItem *oldItem, QTableWidgetItem *newItem);

	private:
		template <class Type>
		void loop(QList<Type> dataList);
		QList<DataObject*> curDataList;

	signals:
		void currentItemChanged(DataObject*);
} ;

#endif //DATATABLEWIDGET_H
