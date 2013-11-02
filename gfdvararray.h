#pragma once

#include <QtCore>

#include "gfdvar.h"

class GFDVarArray : public GFDVar
{
public:
	GFDVarArray();
	virtual GFDVar &operator [] (int index) {
		return *_varsList[index];
	}
	virtual void addValue(GFDVar *value) {
		_varsList.append(value);
	}
	virtual QString toText(bool inArray = false) const;
	virtual uint arraySize() {
		return _varsList.size();
	}
private:
	QVector <GFDVar*> _varsList;

};
