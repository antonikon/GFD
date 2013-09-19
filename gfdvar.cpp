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
