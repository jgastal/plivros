#include "AddTheme.h"

#include "MainWindow.h"
#include "Theme.h"

AddTheme::AddTheme(QWidget *parent) : QWidget(parent)
{
	this->parent = parent;
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
}

void AddTheme::close()
{
	QTabWidget *w = (QTabWidget*)parent;
	w->removeTab(w->currentIndex());
}

bool AddTheme::validateInput()
{
	if(nameLineEdit->text().isEmpty())
		return false;
	return true;
}
