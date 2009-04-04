#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

#include "Section.h"

class Collection;
class QButtonGroup;

class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		OperationsWidget(Collection *c, Section::section s, QWidget *parent = 0);
		void setSection(Section::section s);
		Section::section getType() const;

	public slots:
		void add();
		void edit();
		void erase();
		void search();
		void setSectionButton();

	protected slots:
		void closeTab();
		void closeTab(int index);
		void setSection(QAbstractButton *bt);

	private:
		Collection *c;
		QButtonGroup *btGroup;
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
