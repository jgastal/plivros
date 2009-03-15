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
 *
 * This constructor in addition to constructing the object sets its icon,
 * text, default button and detailed text.
 */
MessageBoxDataBaseException::MessageBoxDataBaseException(DataBaseException *dbe, QWidget *parent) : QMessageBox(parent)
{
	setIcon(QMessageBox::Critical);
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
