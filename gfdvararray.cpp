#include "gfdvararray.h"

GFDVarArray::GFDVarArray()
{
	setType(GFD_VAR_TYPE_ARRAY);
}

QString GFDVarArray::toText(bool inArray) const {
	QString text;
	if (!inArray) {
		text.append(QString("%1 = [").arg(getName()));
	} else {
		text.append("[");
	}
	for (int q = 0; q < _varsList.size(); q++) {
		text.append(_varsList[q]->toText(true));
	}
	text.append("];");
	if (!inArray) {
		text.append("\n");
	}
	return text;
}
