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

class Collection;

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

	private slots:
		void createAddThemeForm();
		void createSearchThemeForm();
		void createAddPublisherForm();
		void createSearchPublisherForm();
		void createAddAuthorForm();
		void createSearchAuthorForm();
		void createAddBookForm();
		void createSearchBookForm();

		//for when buttons are hovered
		void themeEnterHover();
		void publisherEnterHover();
		void authorEnterHover();
		void bookEnterHover();
		void leaveHover();

	private:
		Collection *c;
} ;

#endif //MAINWINDOW_H
