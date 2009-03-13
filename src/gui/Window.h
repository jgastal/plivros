#ifndef WINDOW_H
#define WINDOW_H

#include "ui_MainWindow.h"

class Window : public QMainWindow, private Ui::MainWindow
{
	public:
		Window(QMainWindow *parent = 0);
} ;

#endif //WINDOW_H
