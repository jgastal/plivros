/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
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
