#pragma once

#include <QtCore>

#include "gfdobject.h"

class GFDObject;

enum GFD_VAR_TYPE {
	GFD_VAR_TYPE_INT = 0,
	GFD_VAR_TYPE_STRING = 1,
	GFD_VAR_TYPE_BOOL = 2,
	GFD_VAR_TYPE_ARRAY = 3,
	GFD_VAR_TYPE_OBJECT = 4
};

class GFDVar
{
public:
	GFDVar();
	template <typename T>
	GFDVar(GFD_VAR_TYPE type, const QString &name, T value);
	void setName(const QString &name) {
		_name = name;
	}
	void setType(GFD_VAR_TYPE type) {
		_type = type;
	}
	void setValue(const QString &value) {
		_strValue = value;
	}
	void setValue(double value) {
		_intValue = value;
	}
	void setValue(bool value) {
		_boolValue = value;
	}
	void setValue(GFDObject *value) {
		_valueObject = value;
	}
	void addArrayValue(GFDVar *var) {
		_arrayValue.append(var);
	}
	QString getName() {
		return _name;
	}
	GFD_VAR_TYPE getType() {
		return _type;
	}
	QString getStrValue() {
		return _strValue;
	}
	double getIntValue() {
		return _intValue;
	}
	bool getBoolValue() {
		return _boolValue;
	}
	GFDVar *getArrayValue(size_t index) {
		return _arrayValue[index];
	}
	GFDObject *getObjectValue() {
		return _valueObject;
	}

private:
	QString _name;
	GFD_VAR_TYPE _type;
	QString _strValue;
	double _intValue;
	bool _boolValue;
	QVector <GFDVar*> _arrayValue;
	GFDObject *_valueObject;
};
