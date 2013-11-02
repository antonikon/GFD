#pragma once

#include <QtCore>

#include "gfdvar.h"

class GFDVarObject : public GFDVar
{
public:
	GFDVarObject();
	virtual GFDVar &operator [](const QString &name) {
		return getVar(name);
	}
	virtual GFDVar &operator [](const char *name) {
		return getVar(QString("%1").arg(name));
	}
	virtual void addValue(GFDVar *value) {
		_varsList.append(value);
	}
	virtual QString toText(bool inArray = false) const;
	QString toTextMain() const;
private:
	GFDVar &getVar(const QString &name);
private:
	QVector <GFDVar*> _varsList;
};

