#ifndef OPERATIONSWIDGET_H
#define OPERATIONSWIDGET_H

#include "ui_OperationsWidget.h"

#include "Section.h"

class Collection;
class QButtonGroup;
class DataObject;
class Theme;
class Publisher;
class Author;
class Book;

class OperationsWidget : public QWidget, protected Ui::OperationsWidget
{
	Q_OBJECT

	public:
		OperationsWidget(Collection *c, Section::section s, QWidget *parent = 0);
		void setSection(Section::section s);
		Section::section getType() const;

	public slots:
		void add();
		void edit(DataObject*);
		void erase(DataObject*);
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
		void createEditThemeForm(Theme *t);
		void createAddPublisherForm();
		void createEditPublisherForm(Publisher *p);
		void createAddAuthorForm();
		void createEditAuthorForm(Author *a);
		void createAddBookForm();
		void createEditBookForm(Book *b);
} ;

#endif //OPERATIONSWIDGET_H
