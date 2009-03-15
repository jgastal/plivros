#include "MessageBoxDataBaseException.h"

MessageBoxDataBaseException::MessageBoxDataBaseException(QWidget *parent) : QMessageBox(parent)
{
	setIcon(QMessageBox::Critical);
	setText(tr("A very serious and unexpected error ocurred.\n"));
	q.setDefaultButton(QMessageBox::Close);
	QString str(tr("What: %1\nCaused by: %2\nError code: %3"));
	str = str.arg(dbe.what());
	str = str.arg(dbe.where().c_str());
	str = str.arg(dbe.getCode());
	setDetailedText(str);
}

void MessageBoxDataBaseException::appendText(QString str)
{
	QString str = text();
	str.append(str);
	setText(str);
}
