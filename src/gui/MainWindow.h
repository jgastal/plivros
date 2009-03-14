#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

	public:
		MainWindow(QMainWindow *parent = 0);

	private slots:
		void createAddThemeForm();
		void createAddPublisherForm();
} ;

#endif //MAINWINDOW_H
