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
/**
 * @file PublisherForm.h
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef PUBLISHERFORM_H
#define PUBLISHERFORM_H

#include "ui_PublisherForm.h"

#include "Theme.h"

class Collection;

/**
 * @class PublisherForm PublisherForm.h
 *
 * @brief This widget is a form to add a publisher.
 */
class PublisherForm : public QWidget, protected Ui::PublisherForm
{
	Q_OBJECT

	public:
		PublisherForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();

	protected slots:
		virtual void save() = 0;
		void logoFileChooser();

	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		Collection *c;
		QList<Theme> themeList;

	signals:
		void closeRequested();
} ;

#endif //PUBLISHERFORM_H
