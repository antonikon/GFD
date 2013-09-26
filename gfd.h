#pragma once

#include <QtCore>

#include "gfdobject.h"
#include "gfdvar.h"

class GFD : public GFDObject
{
public:
	GFD(const QString &name);
	GFD();
	void save(QString fileName = "");
private:
	bool parsing(QString &data, GFDObject *object);
	bool parsValue(GFDVar *var, QString &text);
	QString formatting(const QString &text);
	int indexOfToken(const QString &text);
	void serializeObject(QString &data, GFDVar *var, bool isMain = false);
	void serializeVar(QString &data, GFDVar *var, bool inArray = false);
	void serializeArray(QString &data, GFDVar *var);
	GFDVar *toVar();
private:
	QString _fileName;
};
