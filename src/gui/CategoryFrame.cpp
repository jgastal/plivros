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
#include "ui_CategoryFrame.h"

#include "CategoryFrame.h"

#include "Section.h"

static QString bgss = "QWidget#%1 { "
"background: url(:bgs/%2);\n"
"background-repeat: no-repeat;\n"
"background-position: center center; }";

CategoryFrame::CategoryFrame(QWidget *parent) : QFrame(parent)
{
	setupUi(this);

	themePushButton->installEventFilter(this);
	publisherPushButton->installEventFilter(this);
	authorPushButton->installEventFilter(this);
	bookPushButton->installEventFilter(this);

	bgss = bgss.arg(parentWidget()->objectName());
}

void CategoryFrame::setThemeText()
{
	themePushButton->setText(tr("Themes"));
	QString ss = themePushButton->styleSheet();
	ss += "\nfont: bold 20pt \"Arno Pro\";";
	themePushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_themes2.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setPublisherText()
{
	publisherPushButton->setText(tr("Publishers"));
	QString ss = publisherPushButton->styleSheet();
	ss += "\nfont: bold 20pt \"Arno Pro\";";
	publisherPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_publishers.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setAuthorText()
{
	authorPushButton->setText(tr("Authors"));
	QString ss = authorPushButton->styleSheet();
	ss += "\nfont: bold 20pt \"Arno Pro\";";
	authorPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_authors.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setBookText()
{
	bookPushButton->setText(tr("Books"));
	QString ss = bookPushButton->styleSheet();
	ss += "\nfont: bold 20pt \"Arno Pro\";";
	bookPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_books2.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setEmptyText(QPushButton *bt)
{
	bt->setText("");
	QString ss = bt->styleSheet();
	ss += "\nfont: bold 20pt \"Arno Pro\";";
	bt->setStyleSheet(ss);
	parentWidget()->setStyleSheet("");
}

void CategoryFrame::themeClicked()
{
	emit clicked(Section::Theme);
}

void CategoryFrame::publisherClicked()
{
	emit clicked(Section::Publisher);
}

void CategoryFrame::authorClicked()
{
	emit clicked(Section::Author);
}

void CategoryFrame::bookClicked()
{
	emit clicked(Section::Book);
}

bool CategoryFrame::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::HoverLeave)
	{
		emit leaveHover();
		setEmptyText(qobject_cast<QPushButton*>(obj));
	}
	else if(event->type() == QEvent::HoverEnter)
	{
		if(obj == themePushButton)
		{
			emit themeHover();
			setThemeText();
		}
		else if(obj == publisherPushButton)
		{
			emit publisherHover();
			setPublisherText();
		}
		else if(obj == authorPushButton)
		{
			emit authorHover();
			setAuthorText();
		}
		else if(obj == bookPushButton)
		{
			emit bookHover();
			setBookText();
		}
	}
	return QFrame::eventFilter(obj, event);
}
