#pragma once

#include "gfdvar.h"

class GFDVarInt : public GFDVar
{
public:
	GFDVarInt();
	virtual void setValue(int value) {
		_intValue = value;
	}
	virtual void setValue(double value) {
		_intValue = value;
	}
	virtual int toInt() const {
		return _intValue;
	}
	virtual double toDouble() const {
		return _intValue;
	}
	virtual QString toQString() const {
		return QString("%1").arg(_intValue);
	}
private:
	int _intValue;
};
