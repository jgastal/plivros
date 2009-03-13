#include <QMainWindow>
#include <QTranslator>

#include "Collection.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

#include "ui_MainWindow.h"

class Window : public QMainWindow, private Ui::MainWindow
{
	public:
		Window(QMainWindow *parent = 0);
} ;

Window::Window(QMainWindow *parent) : QMainWindow(parent)
{
	setupUi(this);
}

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
