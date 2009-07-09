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
 * @file PropertiesGroupBox.h
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef PROPERTIESGROUPBOX_H
#define PROPERTIESGROUPBOX_H

#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>

#include "Section.h"

class PropertiesGroupBox : public QGroupBox
{
	public:
		PropertiesGroupBox(QWidget *parent = 0);
		void init(Section::section t);
		unsigned short int getSelectedRadioButton() throw(std::out_of_range);

	private:
		QGridLayout grid;
		QList<QRadioButton*> radButtons;
		Section::section t;
} ;

#endif //PROPERTIESGROUPBOX_H
