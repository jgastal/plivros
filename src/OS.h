#include <QDir>
#include <QString>

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
	static const QString dbPath = QCoreApplication::applicationDirPath()+"/dbs/";
	static int initPaths()
	{
		QDir::addSearchPath("resource", QCoreApplication::applicationDirPath()+"/resources/");
		QDir::addSearchPath("fonts", QCoreApplication::applicationDirPath()+"/fonts/");
		return 1;
	}
	static const int inited = initPaths();
#else //*nix
	#include <cstdlib>
	static const QString USERNAME = getenv("USER");
	static const QString dbPath = QDir::homePath().append("/.plivros/");
	static int initPaths()
	{
		QDir::addSearchPath("resource", "/usr/share/plivros/");
		QDir::addSearchPath("fonts", "/usr/share/fonts/misc/");
		return 1;
	}
	static const int inited = initPaths();
#endif //WIN32
