#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

#include "Section.h"

class Collection;

class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		OperationsWidget(Collection *c, Section::section s, QWidget *parent = 0);
		void setSection(Section::section s);
		Section::section getType() const;

	protected slots:
		void add();
		void edit();
		void erase();
		void search();
		void closeTab();

	private:
		Collection *c;
		Section::section section;

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
