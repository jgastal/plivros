/**
 * @file main.cpp
 *
 * @date 09/11/2008
 * @author Jonas M. Gastal
 * @brief Just serves as an entry point.
 */

#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include "MainWindow.h"

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

#ifdef WIN32
	///TODO: Windows specific way of getting user name
	#include <windows.h>
	static const char c_str[256];
	GetUserName(c_str, 0)
	static const QString USERNAME(c_str);
#else //*nix
	#include <cstdlib>
	static const QString USERNAME = getenv("USER");
#endif //WIN32

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTranslator translator;

	//translate to currently used locale
	QString locale = QLocale::system().name();
	translator.load(QString("plivros_") + locale);
	app.installTranslator(&translator);

	MainWindow mw(USERNAME);
	mw.show();
	return app.exec();
}
