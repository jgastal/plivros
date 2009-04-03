#ifndef CATEGORYFRAME_H
#define CATEGORYFRAME_H

#include "ui_CategoryFrame.h"

#include "Section.h"

class CategoryFrame : public QFrame, protected Ui::CategoryFrame
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

	private slots:
		void themeClicked();
		void publisherClicked();
		void authorClicked();
		void bookClicked();

	signals:
		void themeHover();
		void publisherHover();
		void authorHover();
		void bookHover();
		void clicked(Section::section);
		void leaveHover();
} ;

#endif //CATEGORYFRAME_H
