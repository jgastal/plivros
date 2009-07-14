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
#include "AuthorDetails.h"

#include <QWidget>
#include <QString>
#include <QList>
#include <QLocale>

AuthorDetails::AuthorDetails(Author *a, QWidget* parent): QWidget(parent)
{
	setupUi(this);
	firstName->setText(a->getFirstName());
	lastName->setText(a->getLastName());
	picture->setPixmap(QPixmap(a->getPicture()));
	descriptionTextBrowser->setText(a->getDescription());
	critiqueTextBrowser->setText(a->getCritique());
	themes->setText(a->getThemesNames());
	QString wikiLink = wikipediaLink->text();
	QString lc = QLocale::system().name();
	lc.truncate(2);
	wikiLink.replace("<lc>", lc);
	wikiLink.replace("<title>", a->getFirstName().append(a->getLastName()).replace(" ", "_"));
	wikipediaLink->setText(wikiLink);
}
