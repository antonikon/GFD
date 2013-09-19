#pragma once

#include <QObject>
#include <QtCore>

#include "gfdobject.h"

class GFD : public QObject, public GFDObject
{
	Q_OBJECT
public:
	GFD(const QString &name, QObject *parent = 0);
	bool parsing(QString &data, GFDObject *object);
	bool parsValue(GFDVar *var, QString &text);
	QString formatting(const QString &text);
signals:
	
public slots:
	
private:

};
