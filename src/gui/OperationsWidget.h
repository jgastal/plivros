#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

class Collection;

class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		enum section
		{
			book,
			author,
			publisher,
			theme
		} ;

		OperationsWidget(Collection *c, section s, QWidget *parent = 0);
		void setType(section s);
		section getType() const;

	protected slots:
		void add();
		void edit();
		void erase();

	private:
		Collection *c;
		section type;

		void createAddThemeForm();
		void createSearchThemeForm();
		void createAddPublisherForm();
		void createSearchPublisherForm();
		void createAddAuthorForm();
		void createSearchAuthorForm();
		void createAddBookForm();
		void createSearchBookForm();
} ;

#endif //OPERATIONSWIDGET_H
