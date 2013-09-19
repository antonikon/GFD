#include "gfdobject.h"

GFDObject::GFDObject()
{
}

GFDVar *GFDObject::getValue(const QString &name)
{
	for (int q = 0; q < _varList.size(); q++) {
		if (_varList[q]->getName() == name) {
			return _varList[q];
		}
	}
}
