#pragma once

#include <QtCore>

enum GFD_VAR_TYPE
{
	GFD_VAR_TYPE_INT = 0,
	GFD_VAR_TYPE_DOUBLE = 1,
	GFD_VAR_TYPE_STRING = 2,
	GFD_VAR_TYPE_BOOL = 3,
	GFD_VAR_TYPE_ARRAY = 4,
	GFD_VAR_TYPE_OBJECT = 5
};


class GFDVar
{
public:
	GFDVar(const QString &name, GFD_VAR_TYPE type);
	GFDVar(GFDVar *var);
	GFDVar();
	GFD_VAR_TYPE getType() const {
		return _type;
	}
	QString getName() const {
		return _name;
	}
	void setType(GFD_VAR_TYPE type) {
		_type = type;
	}
	void setName(const QString &name) {
		_name = name;
	}
	virtual void setValue(bool value) {Q_UNUSED(value)}
	virtual void setValue(int value) {Q_UNUSED(value)}
	virtual void setValue(double value) {Q_UNUSED(value)}
	virtual void setValue(const QString &value) {Q_UNUSED(value)}
	virtual void addValue(GFDVar *value) {Q_UNUSED(value)}

	virtual int toInt() const {
		return 0;
	}
	virtual double toDouble() const {
		return 0;
	}
	virtual bool toBool() const {
		return false;
	}
	virtual QString toQString() const {
		return "";
	}
	virtual GFDVar &operator [] (int index) {
		Q_UNUSED(index);
		return *this;
	}
	virtual GFDVar &operator [] (const char *name) {
		Q_UNUSED(name);
		return *this;
	}
	virtual GFDVar &operator [] (const QString &name) {
		Q_UNUSED(name);
		return *this;
	}

private:
	GFD_VAR_TYPE _type;
	QString _name;
};
