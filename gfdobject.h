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
	GFDVar &operator[](const QString &name);
	GFDVar &getVar(const QString &name);
	size_t getSize() {
		return _varList.size();
	}
	GFDVar *getVar(size_t index) {
		return _varList[index];
	}
private:
	QVector <GFDVar*> _varList;
};
