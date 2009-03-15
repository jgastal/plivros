#include <QMessageBox>

#include "AddTheme.h"

#include "MainWindow.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Theme.h"

AddTheme::AddTheme(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
	this->c = c;
	setupUi(this);
	connect(addPushButton, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void AddTheme::add()
{
	if(!validateInput())
		return;
	Theme t;
	t.setName(nameLineEdit->text().toStdString());
	t.setDescription(descriptionLineEdit->text().toStdString());
	try
	{
		c->insertTheme(t);
	}
	catch(DataBaseException dbe)
	{
		QMessageBox q(this);
		q.setIcon(QMessageBox::Critical);
		q.setText(tr("A very serious and unexpected error ocurred.\nYour theme has not been added."));
		q.setDefaultButton(QMessageBox::Close);
		QString str(tr("What: %1\nCaused by: %2\nError code: %3"));
		str = str.arg(dbe.what());
		str = str.arg(dbe.where().c_str());
		str = str.arg(dbe.getCode());
		q.setDetailedText(str);
		q.exec();
	}
	close();
}

void AddTheme::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

bool AddTheme::validateInput()
{
	if(!nameLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setText(tr("You must enter the theme name."));
	q.setDefaultButton(QMessageBox::Retry);
	q.exec();
	nameLineEdit->setFocus();
	return false;
}
