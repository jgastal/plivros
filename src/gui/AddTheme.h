#ifndef ADDTHEME_H
#define ADDTHEME_H

#include "ui_AddTheme.h"

class AddTheme : public QWidget, private Ui::AddTheme
{
	Q_OBJECT

	public:
		AddTheme(QWidget *parent = 0);

	private slots:
		void add();
		void close();

	private:
		bool validateInput();
		QWidget *parent;
} ;

#endif //ADDTHEME_H
