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
 * @file MessageBoxDataBaseException.cpp
 *
 * @date 15/03/2009
 * @author Jonas M. Gastal
 * @brief Implements MessageBoxDataBaseException class.
 */

#include "MessageBoxDataBaseException.h"

#include "DataBaseException.h"

/**
 * @brief Constructor
 *
 * @param parent Parent of this widget passed on to QMessageBox constructor.
 * @param dbe DataBaseException from which to get messages.
 *
 * This constructor in addition to constructing the object sets its icon,
 * text, default button and detailed text.
 */
MessageBoxDataBaseException::MessageBoxDataBaseException(DataBaseException *dbe, QWidget *parent) : QMessageBox(parent)
{
	setIcon(QMessageBox::Critical);
	setWindowTitle(tr("Data Base Error"));
	setText(tr("A very serious and unexpected error ocurred.\n"));
	setDefaultButton(QMessageBox::Close);
	QString str(tr("What: %1\nCaused by: %2\nError code: %3"));
	str = str.arg(dbe->what());
	str = str.arg(dbe->where().c_str());
	str = str.arg(dbe->getCode());
	setDetailedText(str);
}

/**
 * @brief Appends \a str to the current text of this object.
 *
 * @param str Text to be appended to current text.
 */
void MessageBoxDataBaseException::appendText(QString str)
{
	QString s = text();
	s.append(str);
	setText(s);
}
