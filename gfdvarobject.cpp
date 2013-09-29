#include "gfdvarobject.h"

GFDVarObject::GFDVarObject()
{
	setType(GFD_VAR_TYPE_OBJECT);
}

GFDVar &GFDVarObject::getVar(const QString &name)
{
	for (int q = 0; q < _varsList.size(); q++) {
		if (_varsList[q]->getName() == name) {
			return *_varsList[q];
		}
	}
	return *this;
}
