#pragma once

#include <QtCore>

#include "gfdvar.h"

class GFDVar;

class GFDObject
{
public:
	GFDObject();
	void addVar(GFDVar *var) {
		_varList.append(var);
	}
	GFDVar *getValue(const QString &name);
private:
	QVector <GFDVar*> _varList;
};
