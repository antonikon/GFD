#pragma once

#include "gfdvar.h"

class GFDVarString : public GFDVar
{
public:
	GFDVarString();
	virtual void setValue(const QString &value) {
		_stringValue = value;
	}
	virtual QString toQString() const {
		return _stringValue;
	}
private:
	QString _stringValue;
};
