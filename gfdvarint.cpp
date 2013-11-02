#include "gfdvarint.h"

GFDVarInt::GFDVarInt():
	_intValue(0)
{
	setType(GFD_VAR_TYPE_INT);
}

QString GFDVarInt::toText(bool inArray) const {
	if (!inArray) {
		return QString("%1 = %2;\n").arg(getName()).arg(_intValue);
	} else {
		return QString("%1;").arg(_intValue);
	}
}
