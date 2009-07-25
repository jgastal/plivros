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
 * @file main.cpp
 *
 * @date 09/11/2008
 * @author Jonas M. Gastal
 * @brief Just serves as an entry point.
 */

#include <QApplication>
#include <QFontDatabase>
#include <QTranslator>
#include <QLocale>
#include <QResource>

#include "MainWindow.h"
#include "OS.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTranslator translator;

	//Makes these fonts available for the program
	//Zurich BT, Zurich Lt BT, Arno Pro
	QFontDatabase::addApplicationFont("fonts:zurich_bt.ttf");
	QFontDatabase::addApplicationFont("fonts:zurich_light_bt.ttf");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-BOLDCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-ITALICCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-CAPTION.OTF");

	//translate to currently used locale
	QString locale = QLocale::system().name();
	translator.load(QString("resource:plivros_") + locale);
	app.installTranslator(&translator);

	//Changes default program font
	app.setFont(QFont("Zurich Lt BT"));
	app.setFont(QFont("Arno Pro"), "HoverPushButton");

	QResource::registerResource("resource:imgs.bqrc");
	QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());

	MainWindow mw(USERNAME);
	mw.show();
	return app.exec();
}
