#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		OperationsWidget(QWidget *parent = 0);

	protected slots:
		/*void createAddThemeForm();
		void createSearchThemeForm();
		void createAddPublisherForm();
		void createSearchPublisherForm();
		void createAddAuthorForm();
		void createSearchAuthorForm();
		void createAddBookForm();
		void createSearchBookForm();*/
} ;

#endif //OPERATIONSWIDGET_H
