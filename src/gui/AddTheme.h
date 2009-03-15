#ifndef ADDTHEME_H
#define ADDTHEME_H

#include "ui_AddTheme.h"

class Collection;

class AddTheme : public QWidget, private Ui::AddTheme
{
	Q_OBJECT

	public:
		AddTheme(Collection *c, QWidget *parent = 0);

	private slots:
		void add();
		void close();

	private:
		bool validateInput();
		QWidget *parent;
		Collection *c;
} ;

#endif //ADDTHEME_H
