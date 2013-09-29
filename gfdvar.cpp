#include "gfdvar.h"

GFDVar::GFDVar(const QString &name, GFD_VAR_TYPE type):
	_type(type),
	_name(name)
{
}

GFDVar::GFDVar(GFDVar *var):
	_type(var->getType()),
	_name(var->getName())
{

}

GFDVar::GFDVar():
	_name("")
{
}
