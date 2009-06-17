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
#include "BookDetails.h"

#include <QWidget>
#include <QString>
#include <QList>

const QString BookDetails::link = QString("<a href=\"<link>\"><span style=\" text-decoration: underline; color:#0000ff;\"><name></span></a>");

BookDetails::BookDetails(Book *b, QWidget* parent): QWidget(parent)
{
	book = b;
	setupUi(this);
	cover->setPixmap(QPixmap(b->getCover()));
	title->setText(b->getTitle());
	initAuthors();
	translator->setText(makeLink((const Author)b->getTranslator()));
	initPublishers();
	pubDate->setText(b->getPubDate().toString());
	edition->setText(QString::number(b->getEdition()));
	udc->setText(b->getUDC());
	descriptionTextBrowser->setText(b->getDescription());
	critiqueTextBrowser->setText(b->getCritique());
	isbn->setText(b->getIsbn());
	QString wikiLink = wikipediaLink->text();
	QString lc = QLocale::system().name();
	lc.truncate(2);
	wikiLink.replace("<lc>", lc);
	wikiLink.replace("<title>", b->getTitle().replace(" ", "_"));
	wikipediaLink->setText(wikiLink);
	ebookLink->setText(ebookLink->text().replace("<ebook>", b->getEbook()));
}

void BookDetails::authorClicked()
{
}

void BookDetails::publisherClicked()
{
}

void BookDetails::initAuthors()
{
	QString html;
	QList<Author> aList = book->getAuthors();
	for(int i = 0; i < aList.size(); i++)
		html.append(makeLink(aList.at(i)));
	authors->setText(html);
}

void BookDetails::initPublishers()
{
	QString html;
	QList<Publisher> pList = book->getPublishers();
	for(int i = 0; i < pList.size(); i++)
		html.append(makeLink(pList.at(i)));
	publishers->setText(html);
}

template <class T>
QString BookDetails::makeLink(T &data)
{
	QString ret = link;
	ret.replace("<link>", "view://"+data.getName());
	ret.replace("<name>", data.getName());
	ret.append("<a>; </a>");
	return ret;
}