/**
 * @file SearchForm.h
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include "ui_SearchForm.h"

#include "Section.h"

#include <QWidget>

class Collection;
class DataObject;

class SearchForm : public QWidget, private Ui::SearchForm
{
	Q_OBJECT

	public:
		SearchForm(Section::section t, Collection *c, QWidget *parent = 0);
		Section::section getType() const;

	private slots:
		void search();

	signals:
		void closeRequested();
		void edit(DataObject*);
		void del(DataObject*);
		void view(DataObject*);

	private:
		Collection *c;
		Section::section t;
} ;

#endif //SEARCHFORM_H
