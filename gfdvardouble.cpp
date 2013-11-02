#include "gfdvardouble.h"

GFDVarDouble::GFDVarDouble():
	_doubleValue(0)
{
	setType(GFD_VAR_TYPE_DOUBLE);
}

QString GFDVarDouble::toText(bool inArray) const {
	if (!inArray) {
		return QString("%1 = %2;\n").arg(getName()).arg(_doubleValue);
	} else {
		return QString("%1;").arg(_doubleValue);
	}
}
