#include <QCoreApplication>

#include "gfd.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	GFD config("config.gfd");
	qDebug() << config["objarray"][1]["name"].toQString();
	return a.exec();
}
