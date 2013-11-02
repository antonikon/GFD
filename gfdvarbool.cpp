#include "gfdvarbool.h"

GFDVarBool::GFDVarBool():
	_boolValue(false)
{
	setType(GFD_VAR_TYPE_BOOL);
}

QString GFDVarBool::toText(bool inArray) const {
	QString boolText;
	if (_boolValue) {
		boolText = "true";
	} else {
		boolText = "false";
	}
	if (!inArray) {
		return QString("%1 = %2;\n").arg(getName()).arg(boolText);
	} else {
		return QString("%1;").arg(boolText);
	}
}
