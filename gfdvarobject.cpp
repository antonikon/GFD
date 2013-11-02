#include "gfdvarobject.h"

GFDVarObject::GFDVarObject()
{
	setType(GFD_VAR_TYPE_OBJECT);
}

QString GFDVarObject::toText(bool inArray) const {
	QString text;
	if (!inArray) {
		text.append(QString("%1 = {\n").arg(getName()));
	} else {
		text.append("{\n");
	}
	for (int q = 0; q < _varsList.size(); q++) {
		text.append(_varsList[q]->toText());
	}
	text.append("};\n");
	return text;
}

QString GFDVarObject::toTextMain() const
{
	QString text;
	for (int q = 0; q < _varsList.size(); q++) {
		text.append(_varsList[q]->toText());
	}
	return text;
}

GFDVar &GFDVarObject::getVar(const QString &name)
{
	for (int q = 0; q < _varsList.size(); q++) {
		if (_varsList[q]->getName() == name) {
			return *_varsList[q];
		}
	}
	return *this;
}
