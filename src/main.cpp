#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include "Window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTranslator translator;

	//translate to currently used locale
	QString locale = QLocale::system().name();
	translator.load(QString("plivros_") + locale);
	app.installTranslator(&translator);

	Window w;
	w.show();
	return app.exec();
}
