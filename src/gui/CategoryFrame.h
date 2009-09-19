/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CATEGORYFRAME_H
#define CATEGORYFRAME_H

#include "ui_CategoryFrame.h"

#include "Section.h"

class CategoryFrame : public QFrame, protected Ui::CategoryFrame
{
	Q_OBJECT

	public:
		CategoryFrame(QWidget *parent = 0);
		virtual bool eventFilter(QObject *watched, QEvent *event);

	protected slots:
		void setThemeText();
		void setPublisherText();
		void setAuthorText();
		void setBookText();
		void setEmptyText(QPushButton *bt);

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
