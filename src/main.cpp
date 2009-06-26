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
#include <QDir>

#include "MainWindow.h"

#ifdef WIN32
	#include <windows.h>
	static QString getUName()
	{
		char uname[256];
		DWORD nUserName = sizeof(uname);
		GetUserName(uname, &nUserName);
		return QString(uname);
	}
	static const QString USERNAME(getUName());
#else //*nix
	#include <cstdlib>
	static const QString USERNAME = getenv("USER");
#endif //WIN32

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTranslator translator;

#ifdef WIN32
	QDir::addSearchPath("resource", QCoreApplication::applicationDirPath()+"/imgs/");
	QDir::addSearchPath("fonts", QCoreApplication::applicationDirPath()+"/fonts/");
#else
	QDir::addSearchPath("resource", "/usr/share/plivros/");
	QDir::addSearchPath("fonts", "/usr/share/fonts/misc/");
#endif

	//Makes these fonts available for the program
	//Zurich BT, Zurich Lt BT, Arno Pro
	QFontDatabase::addApplicationFont("fonts:zurich_bt.ttf");
	QFontDatabase::addApplicationFont("fonts:zurich_light_bt.ttf");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-BOLDCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-ITALICCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts:ARNOPRO-CAPTION.OTF");

	//translate to currently used locale
	QString locale = QLocale::system().name();
	translator.load(QString("plivros_") + locale);
	app.installTranslator(&translator);

	//Changes default program font
	app.setFont(QFont("Zurich Lt BT"));
	app.setFont(QFont("Arno Pro"), "HoverPushButton");

	QResource::registerResource("resource:imgs.big");
	QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());

	MainWindow mw(USERNAME);
	mw.show();
	return app.exec();
}
