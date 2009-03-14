#include "Window.h"

Window::Window(QMainWindow *parent) : QMainWindow(parent)
{
	setupUi(this);
	connect(themesAdd, SIGNAL(released()), this, SLOT(createAddThemeForm()));
	connect(publisherAdd, SIGNAL(released()), this, SLOT(createAddPublisherForm()));
}

void Window::createAddThemeForm()
{
}

void Window::createAddPublisherForm()
{
}
