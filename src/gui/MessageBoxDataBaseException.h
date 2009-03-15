#ifndef MESSAGEBOXDATABASEEXCEPTION_H
#define MESSAGEBOXDATABASEEXCEPTION_H

#include <QMessageBox>

class MessageBoxDataBaseException : public QMessageBox
{
	public:
		MessageBoxDataBaseException(QWidget *parent = 0);
		void appendText(QString str);
}

#endif //MESSAGEBOXDATABASEEXCEPTION_H
