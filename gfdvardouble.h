#pragma once

#include "gfdvar.h"

class GFDVarDouble : public GFDVar
{
public:
	GFDVarDouble();
	virtual double toDouble() const {
		return _doubleValue;
	}
	virtual int toInt() const {
		return _doubleValue;
	}
	virtual QString toQString() const {
		return QString("%1").arg(_doubleValue);
	}
	virtual void setValue(double value) {
		_doubleValue = value;
	}
	virtual void setValue(int value) {
		_doubleValue = value;
	}
	virtual QString toText(bool inArray = false) const;
private:
	double _doubleValue;
};
