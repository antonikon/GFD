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
	~GFDVar();
	template <typename T>
	GFDVar(GFD_VAR_TYPE type, const QString &name, T value);
	void setName(const QString &name) {
		_name = name;
	}
	void setValue(const char *value) {
		_type = GFD_VAR_TYPE_STRING;
		_strValue = QString("%1").arg(value);
		_intValue = 0;
		_boolValue = false;
		_objectValue = nullptr;
	}
	void setValue(const QString &value) {
		_type = GFD_VAR_TYPE_STRING;
		_strValue = value;
		_intValue = 0;
		_boolValue = false;
		_objectValue = nullptr;
	}
	void setValue(double value) {
		_type = GFD_VAR_TYPE_INT;
		_intValue = value;
		_strValue = QString("%1").arg(value);
		_boolValue = false;
		_objectValue = nullptr;
	}
	void setValue(int value) {
		_type = GFD_VAR_TYPE_INT;
		_intValue = value;
		_strValue = QString("%1").arg(value);
		_boolValue = false;
		_objectValue = nullptr;
	}
	void setValue(bool value) {
		_type = GFD_VAR_TYPE_BOOL;
		_boolValue = value;
		_intValue = value;
		_strValue = QString("%1").arg(value);
		_objectValue = nullptr;
	}
	void setValue(GFDObject *value) {
		_type = GFD_VAR_TYPE_OBJECT;
		_strValue = "";
		_intValue = 0;
		_boolValue = false;
		_objectValue = value;
	}
	void addArrayValue(GFDVar var) {
		_type = GFD_VAR_TYPE_ARRAY;
		_arrayValue.append(var);
	}
	QString getName() {
		return _name;
	}
	GFD_VAR_TYPE getType() {
		return _type;
	}
	size_t getArraySize() {
		return _arrayValue.size();
	}
	operator QString() {
		return _strValue;
	}
	operator const char*() {
		return _strValue.toLocal8Bit().data();
	}
	operator double() {
		return _intValue;
	}
	operator float() {
		return _intValue;
	}
	operator int() {
		return _intValue;
	}
	operator bool() {
		return _boolValue;
	}
	QString toQString() {
		return _strValue;
	}
	double toDouble() {
		return _intValue;
	}
	bool toBool() {
		return _boolValue;
	}
	GFDObject *toObject() {
		return _objectValue;
	}
	GFDVar &operator [](int index) {
		return _arrayValue[index];
	}
	GFDVar &operator [](const char *name);
	GFDVar &operator [](QString name);
	GFDVar *getArrayVar(size_t index) {
		return &_arrayValue[index];
	}

private:
	QString _name;
	GFD_VAR_TYPE _type;
	QString _strValue;
	double _intValue;
	bool _boolValue;
	QVector <GFDVar> _arrayValue;
	GFDObject *_objectValue;
};
