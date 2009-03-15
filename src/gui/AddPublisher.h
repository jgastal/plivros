#ifndef ADDPUBLISHER_H
#define ADDPUBLISHER_H

#include "ui_AddPublisher.h"

#include "Theme.h"

class Collection;

class AddPublisher : public QWidget, private Ui::AddPublisher
{
	Q_OBJECT

	public:
		AddPublisher(Collection *c, QWidget *parent = 0);

	private slots:
		//void add();
		void close();
		
	private:
		bool validateInput();
		QWidget *parent;
		Collection *c;
		QList<Theme> themeList;
} ;

#endif //ADDPUBLISHER_H
