#include <QList>
#include <QFileDialog>

#include "AuthorForm.h"
#include "MessageBoxDataBaseException.h"

#include "Collection.h"
#include "DataBaseException.h"
#include "Author.h"
#include "Theme.h"

AuthorForm::AuthorForm(Collection *c, QWidget *parent) : QWidget(parent)
{
	this->c = c;
	setupUi(this);
	populateThemesListWidget();
	connect(savePushButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(cancelPushButton, SIGNAL(clicked()), this, SIGNAL(closeRequested()));
	connect(picturePushButton, SIGNAL(clicked()), this, SLOT(picFileChooser()));
}

bool AuthorForm::validateInput()
{
	if(!firstNameLineEdit->text().isEmpty() && !lastNameLineEdit->text().isEmpty())
		return true;
	QMessageBox q(this);
	q.setIcon(QMessageBox::Warning);
	q.setWindowTitle(tr("Invalid input"));
	q.setText(tr("You must enter the author's name."));
	q.setDefaultButton(QMessageBox::Retry);
	q.exec();
	if(firstNameLineEdit->text().isEmpty())
		firstNameLineEdit->setFocus();
	else if(lastNameLineEdit->text().isEmpty())
		lastNameLineEdit->setFocus();
	return false;
}

QList<Theme> AuthorForm::getSelectedThemes()
{
	QList<Theme> list;
	for(int i = 0; i < themesListWidget->count(); i++)
	{
		if(themesListWidget->item(i)->isSelected())
			list.append(themeList.at(i));
	}
	return list;
}

///@brief Filles themesListWidget with all existing themes.
void AuthorForm::populateThemesListWidget()
{
	try
	{
		themeList = c->searchThemes(Theme::t_name, "");
		QStringList strList;
		for(QList<Theme>::iterator it = themeList.begin(); it != themeList.end(); it++)
			strList.append(it->getName());
		themesListWidget->clear();
		themesListWidget->insertItems(0, strList);
	}
	catch(DataBaseException dbe)
	{
		MessageBoxDataBaseException q(&dbe, this);
		q.appendText(tr("Couldn't populate list of themes.\nClosing this tab."));
		q.exec();
	}
}

///@brief Shows file chooser and puts chosen file in logoLineEdit.
void AuthorForm::picFileChooser()
{
	QFileDialog d(this);
	d.setFileMode(QFileDialog::ExistingFile);
	d.setViewMode(QFileDialog::Detail);
	d.exec();
	QStringList strList = d.selectedFiles();
	if(strList.count())
		pictureLineEdit->setText(strList.first());
}
