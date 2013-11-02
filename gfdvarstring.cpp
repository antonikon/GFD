#include "gfdvarstring.h"

GFDVarString::GFDVarString()
{
	setType(GFD_VAR_TYPE_STRING);
}

QString GFDVarString::toText(bool inArray) const {
	if (!inArray) {
		return QString("%1 = \"%2\";\n").arg(getName()).arg(_stringValue);
	} else {
		return QString("\"%1\";").arg(_stringValue);
	}
}
