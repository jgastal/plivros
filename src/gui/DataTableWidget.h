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
class QAction;

class DataTableWidget : public QTableWidget
{
	Q_OBJECT

	public:
		DataTableWidget(QWidget *parent = 0);
		virtual ~DataTableWidget();

	public slots:
		void populateTable(QList<Book> dataList);
		void populateTable(QList<Author> dataList);
		void populateTable(QList<Publisher> dataList);
		void populateTable(QList<Theme> dataList);

	signals:
		void edit(DataObject*);
		void del(DataObject*);
		void view(DataObject*);

	private slots:
		void edit();
		void del();
		void view();

	private:
		template <class Type>
		void loop(QList<Type> dataList);
		void initActions();
		QList<DataObject*> curDataList;
		QAction *edit_act;
		QAction *del_act;
		QAction *view_act;
} ;

#endif //DATATABLEWIDGET_H
