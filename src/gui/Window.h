#ifndef WINDOW_H
#define WINDOW_H

#include "ui_MainWindow.h"

class Window : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

	public:
		Window(QMainWindow *parent = 0);

	private slots:
		void createAddThemeForm();
		void createAddPublisherForm();
} ;

#endif //WINDOW_H
