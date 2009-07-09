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
#include "PublisherDetails.h"

#include <QWidget>
#include <QString>
#include <QList>
#include <QLocale>

PublisherDetails::PublisherDetails(Publisher *p, QWidget* parent): QWidget(parent)
{
	setupUi(this);
	name->setText(p->getName());
	logo->setPixmap(QPixmap(p->getLogo()));
	descriptionTextBrowser->setText(p->getDescription());
	critiqueTextBrowser->setText(p->getCritique());
	themes->setText(p->getThemesNames());
	QString wikiLink = wikipediaLink->text();
	QString lc = QLocale::system().name();
	lc.truncate(2);
	wikiLink.replace("<lc>", lc);
	wikiLink.replace("<title>", p->getName().replace(" ", "_"));
	wikipediaLink->setText(wikiLink);
}
