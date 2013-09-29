#pragma once

#include "gfdvar.h"

class GFDVarBool : public GFDVar
{
public:
	GFDVarBool();
	virtual void setValue(bool value) {
		_boolValue = value;
	}
	virtual bool toBool() const{
		return _boolValue;
	}

private:
	bool _boolValue;
};
