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
signals:
	
public slots:
	

private:
	bool parsing(QString &data, GFDObject *object);
	bool parsValue(GFDVar *var, QString &text);
	QString formatting(const QString &text);
	int indexOfToken(const QString &text);
};
