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

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

#ifdef WIN32
	///TODO: Windows specific way of getting user name
	/*#include <windows.h>
	static const char c_str[256];
	GetUserName(c_str, 0)*/
	static const QString USERNAME("username");
#else //*nix
	#include <cstdlib>
	static const QString USERNAME = getenv("USER");
#endif //WIN32

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTranslator translator;

	//Makes these fonts available for the program
	//Zurich BT, Zurich Lt BT, Arno Pro
	QFontDatabase::addApplicationFont("fonts/zurich_bt.ttf");
	QFontDatabase::addApplicationFont("fonts/zurich_light_bt.ttf");
	QFontDatabase::addApplicationFont("fonts/ARNOPRO-BOLDCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts/ARNOPRO-ITALICCAPTION.OTF");
	QFontDatabase::addApplicationFont("fonts/ARNOPRO-CAPTION.OTF");

	//translate to currently used locale
	QString locale = QLocale::system().name();
	translator.load(QString("plivros_") + locale);
	app.installTranslator(&translator);

	//Changes default program font
	app.setFont(QFont("Zurich Lt BT"));
	app.setFont(QFont("Arno Pro"), "HoverPushButton");

	QResource::registerResource(QCoreApplication::applicationDirPath().append("/imgs/imgs.big"));
	MainWindow mw(USERNAME);
	mw.show();
	return app.exec();
}
