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
#ifndef PUBLISHERDETAILS_H
#define PUBLISHERDETAILS_H

#include <QWidget>
#include <QString>

#include "ui_PublisherDetails.h"
#include "Publisher.h"

class PublisherDetails : public QWidget, protected Ui::PublisherDetails
{
	Q_OBJECT

	public:
		PublisherDetails(Publisher &p, QWidget* parent = 0);
};

#endif // PUBLISHERDETAILS_H
