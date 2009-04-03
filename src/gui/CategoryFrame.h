#ifndef CATEGORYFRAME_H
#define CATEGORYFRAME_H

#include "ui_CategoryFrame.h"

class CategoryFrame : public QWidget, protected Ui::CategoryFrame
{
	Q_OBJECT

	public:
		CategoryFrame(QWidget *parent = 0);

	protected slots:
		void setThemeText();
		void setPublisherText();
		void setAuthorText();
		void setBookText();
		void setEmptyText();

	signals:
		void themeHover();
		void publisherHover();
		void authorHover();
		void bookHover();
		void leaveHover();
} ;

#endif //CATEGORYFRAME_H
