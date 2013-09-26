#include "gfdobject.h"

GFDObject::GFDObject()
{
}

GFDObject::~GFDObject()
{
	for (int q = 0; q < _varList.size(); q++) {
		delete _varList[q];
	}
	_varList.clear();
}

GFDVar &GFDObject::operator[](const QString &name)
{
	for (int q = 0; q < _varList.size(); q++) {
		if (_varList[q]->getName() == name) {
			return *_varList[q];
		}
	}
}

GFDVar &GFDObject::getVar(const QString &name)
{
	for (int q = 0; q < _varList.size(); q++) {
		if (_varList[q]->getName() == name) {
			return *_varList[q];
		}
	}
}
