/**
 * @file MainWindow.h
 *
 * @date 13/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include "Section.h"

class Collection;
class CategoryFrame;
class OperationsWidget;

/**
 * @class MainWindow MainWindow.h
 *
 * @brief This is the main window of the program offering a start point to the user interface.
 */
class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

	public:
		MainWindow(QString userName = "User", QMainWindow *parent = 0);
		~MainWindow();

	protected slots:
		void createOpsWidget(Section::section s);
		void home();

	private:
		Collection *c;
		CategoryFrame *cf;
		OperationsWidget *ow;
} ;

#endif //MAINWINDOW_H
