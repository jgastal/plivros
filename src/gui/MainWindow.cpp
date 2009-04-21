/**
 * @file MainWindow.cpp
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class implementation.
 */

/**
 * TODO: searchLabel above searchLineEdit?
 */

#include "CategoryFrame.h"
#include "OperationsWidget.h"
#include "Section.h"

#include "MainWindow.h"

#include "Collection.h"

///@brief Constructor. Creates a collection, setups the gui and connects slots and signals.
MainWindow::MainWindow(QString userName, QMainWindow *parent) : QMainWindow(parent)
{
	c = new Collection(userName);
	setupUi(this);

	connect(quitLabel, SIGNAL(linkActivated(QString)), this, SLOT(close()));

	QString userStr = userLabel->text();
	userStr.replace("<user>", userName);
	userLabel->setText(userStr);

	ow = 0;
	cf = new CategoryFrame(displayWidget);
	connect(cf, SIGNAL(clicked(Section::section)), this, SLOT(createOpsWidget(Section::section)));
	displayWidget->layout()->addWidget(cf);
}

MainWindow::~MainWindow()
{
	delete c;
}

void MainWindow::createOpsWidget(Section::section s)
{
	if(!ow)
	{
		ow = new OperationsWidget(c, s, displayWidget);
		displayWidget->layout()->addWidget(ow);
	}
	else
	{
		ow->setSection(s);
		ow->setSectionButton();
		ow->add();
	}

	cf->hide();
	ow->show();
}

void MainWindow::home()
{
	if(ow)
		ow->hide();
	cf->show();
}
