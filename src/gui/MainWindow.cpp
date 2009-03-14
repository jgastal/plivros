#include "AddTheme.h"
#include "AddPublisher.h"

#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	setupUi(this);
	tabWidget->clear();
	connect(themesAdd, SIGNAL(released()), this, SLOT(createAddThemeForm()));
	connect(publisherAdd, SIGNAL(released()), this, SLOT(createAddPublisherForm()));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

void MainWindow::createAddThemeForm()
{
	tabWidget->setUpdatesEnabled(false);
	int pos = tabWidget->addTab(new AddTheme(tabWidget), tr("Add Theme"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void MainWindow::createAddPublisherForm()
{
	tabWidget->setUpdatesEnabled(false);
	int pos = tabWidget->addTab(new AddPublisher(tabWidget), tr("Add Publisher"));
	tabWidget->setCurrentIndex(pos);
	tabWidget->setUpdatesEnabled(true);
}

void MainWindow::closeTab(int index)
{
	tabWidget->removeTab(index);
}
