#pragma once

#include <QtCore>

#include "gfdvar.h"
#include "gfdvarobject.h"
#include "gfdvararray.h"
#include "gfdvarbool.h"
#include "gfdvardouble.h"
#include "gfdvarint.h"
#include "gfdvarstring.h"

class GFD: public GFDVarObject
{
public:
	GFD(const QString &filename);
	GFD();
	void openFile(const QString &filename);
	void saveFile(QString name = "");
	bool parse(QString &data, GFDVarObject *object);
private:
	QString readFile();
	void formatting(QString &data);
	int indexOfToken(QString &data);
	QString parseVarName(QString &data);
	bool parseVar(GFDVar *&var, QString &data);
private:
	QString _fileName;
};
