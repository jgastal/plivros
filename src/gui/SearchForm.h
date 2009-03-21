#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include "ui_SearchForm.h"

#include "PropertiesGroupBox.h"

#include <QWidget>

class Collection;
class DataObject;

class SearchForm : public QWidget, private Ui::SearchForm
{
	Q_OBJECT

	public:
		SearchForm(PropertiesGroupBox::type t, Collection *c, QWidget *parent = 0);
		PropertiesGroupBox::type getType() const;

	private slots:
		void search();

	signals:
		void closeRequested();
		void currentItemChanged(DataObject*);

	private:
		Collection *c;
		PropertiesGroupBox::type t;
} ;

#endif //SEARCHFORM_H
