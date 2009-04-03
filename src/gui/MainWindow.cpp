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
	c = new Collection("User");
	setupUi(this);

	connect(quitLabel, SIGNAL(linkActivated(QString)), this, SLOT(close()));

	QString userStr = userLabel->text();
	userStr.replace("<user>", userName);
	userLabel->setText(userStr);

	cf = new CategoryFrame();
	connect(cf, SIGNAL(clicked(Section::section)), this, SLOT(createOpsWidget(Section::section)));
	displayWidget->layout()->addWidget(cf);
}

MainWindow::~MainWindow()
{
	delete c;
}

void MainWindow::createOpsWidget(Section::section s)
{
	OperationsWidget *ow;
	if(s == Section::Book)
		ow = new OperationsWidget(c, Section::Book);
	else if(s == Section::Author)
		ow = new OperationsWidget(c, Section::Author);
	else if(s == Section::Publisher)
		ow = new OperationsWidget(c, Section::Publisher);
	else if(s == Section::Theme)
		ow = new OperationsWidget(c, Section::Theme);

	cf->hide();
	displayWidget->layout()->addWidget(ow);
}
