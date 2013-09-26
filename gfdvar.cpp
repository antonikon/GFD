#include "gfdvar.h"

template <typename T>
GFDVar::GFDVar(GFD_VAR_TYPE type, const QString &name, T value):
	_type(type),
	_name(name)
{
	setValue(value);

}

GFDVar::GFDVar()
{

}

GFDVar::~GFDVar()
{
	if (_type == GFD_VAR_TYPE_OBJECT) {
		delete _objectValue;
	}
}

GFDVar &GFDVar::operator [](const char *name)
{
	return _objectValue->getVar(name);
}

GFDVar &GFDVar::operator [](QString name)
{
	return _objectValue->getVar(name);
}
