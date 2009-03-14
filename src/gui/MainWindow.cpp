#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	setupUi(this);
	connect(themesAdd, SIGNAL(released()), this, SLOT(createAddThemeForm()));
	connect(publisherAdd, SIGNAL(released()), this, SLOT(createAddPublisherForm()));
}

void MainWindow::createAddThemeForm()
{
}

void MainWindow::createAddPublisherForm()
{
}
