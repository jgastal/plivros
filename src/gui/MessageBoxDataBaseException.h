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
 * @file MessageBoxDataBaseException.h
 *
 * @date 15/03/2009
 * @author Jonas M. Gastal
 * @brief Defines MessageBoxDataBaseException class.
 */

#ifndef MESSAGEBOXDATABASEEXCEPTION_H
#define MESSAGEBOXDATABASEEXCEPTION_H

#include <QMessageBox>

class DataBaseException;

/**
 * @class MessageBoxDataBaseException MessageBoxDataBaseException.h
 *
 * @brief This class is a wrapper around QMessageBox to display DataBaseExceptions.
 *
 * This class inherits from QMessageBox. It was created as a convenient way to
 * write less code, it sets a number of presets to the QMessageBox that are good
 * for DataBaseExceptions, such as: Icon, Detailed text, Default button and a text
 * that says the error was unexpected and serious. Also provided for convenience
 * is a method to append to text.
 */
class MessageBoxDataBaseException : public QMessageBox
{
	Q_OBJECT

	public:
		MessageBoxDataBaseException(DataBaseException *dbe, QWidget *parent = 0);
		void appendText(QString str);
} ;

#endif //MESSAGEBOXDATABASEEXCEPTION_H
