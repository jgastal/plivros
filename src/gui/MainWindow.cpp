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
	displayWidget->layout()->addWidget(cf);
}

MainWindow::~MainWindow()
{
	delete c;
}
