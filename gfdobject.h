#pragma once

#include <QtCore>

#include "gfdvar.h"

class GFDVar;

class GFDObject
{
public:
	GFDObject();
	~GFDObject();
	void addVar(GFDVar *var) {
		_varList.append(var);
	}
	GFDVar operator[](const QString &name);
	GFDVar getVar(const QString &name);
private:
	QVector <GFDVar*> _varList;
};
