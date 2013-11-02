#include <QCoreApplication>

#include "gfd.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	GFD config("config1.gfd");
	config.saveFile("config.gfd");
	return a.exec();
}
