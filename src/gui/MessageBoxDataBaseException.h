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
	public:
		MessageBoxDataBaseException(QWidget *parent = 0);
		void appendText(QString str);
}

#endif //MESSAGEBOXDATABASEEXCEPTION_H
