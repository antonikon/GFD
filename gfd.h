#pragma once

#include <QObject>
#include <QtCore>

#include "gfdobject.h"
#include "gfdvar.h"

class GFD : public QObject, public GFDObject
{
	Q_OBJECT
public:
	GFD(const QString &name, QObject *parent = 0);
	GFD(QObject *parent = 0);
	void save(QString fileName = "");
signals:
	
public slots:
	

private:
	bool parsing(QString &data, GFDObject *object);
	bool parsValue(GFDVar *var, QString &text);
	QString formatting(const QString &text);
	int indexOfToken(const QString &text);
	void serializeObject(QString &data, GFDVar *var);
	void serializeVar(QString &data, GFDVar *var, bool inArray = false);
	void serializeArray(QString &data, GFDVar *var);
	GFDVar *toVar();
private:
	QString _fileName;
};
