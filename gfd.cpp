#include "gfd.h"

GFD::GFD(const QString &filename):
	_fileName(filename)
{
	QString data = readFile();
	parse(data,this);
}

GFD::GFD():
	_fileName("")
{
}

void GFD::openFile(const QString &filename)
{
	_fileName = filename;
	QString data = readFile();
	parse(data,this);
}

void GFD::saveFile(QString name)
{
	if (name == "") {
		name = _fileName;
	}
	QString text = toTextMain();
	QFile file(name);
	file.open(QFile::WriteOnly);
	file.write(text.toLocal8Bit());
	file.close();

}

bool GFD::parse(QString &data, GFDVarObject *object)
{
	formatting(data);
	int index = indexOfToken(data);
	while (index != -1) {
		QString line =  data.left(index);
		QString varName;
		GFDVar *var = nullptr;

		data.remove(0, index + 1);

		varName = parseVarName(line);
		bool status = parseVar(var, line);
		if (!status) return false;
		var->setName(varName);
		index = indexOfToken(data);
		object->addValue(var);
	}
	return true;
}

QString GFD::readFile()
{
	QFile file(_fileName);
	file.open(QFile::ReadOnly);
	QString data = file.readAll();
	file.close();
	return data;
}

void GFD::formatting(QString &data)
{
	bool inText = false;
	for (int q = 0; q < data.size(); q++) {
		if (data[q] == '"') {
			inText = !inText;
		} else if (!inText) {
			if (data[q] == ' ') {
				data.remove(q,1);
				q--;
			} else if (data[q] == '\t') {
				data.remove(q,1);
				q--;
			} else if (data[q] == '\n') {
				data.remove(q,1);
				q--;
			}
		}
	}
}

int GFD::indexOfToken(QString &data)
{
	uint openToken = 0;
	bool inText = false;
	int index = -1;

	for (int q = 0; q < data.size(); q++) {
		if (data[q] == '"') {
			inText = !inText;
		} else if (!inText) {
			if (data[q] == '[') {
				openToken++;
			} else if (data[q] == ']') {
				openToken--;
			} else if (data[q] == '{') {
				openToken++;
			} else if (data[q] == '}') {
				openToken--;
			}  else if ((data[q] == ';') & (openToken == 0)) {
				index = q;
				break;
			}
		}
	}
	if ((index == -1) & (data.size() > 0)) {
		index = data.size();
	}
	return index;
}

QString GFD::parseVarName(QString &data)
{
	int index = data.indexOf('=');
	QString name = data.left(index);
	data.remove(0, index + 1);
	return name;
}

bool GFD::parseVar(GFDVar *&var, QString &data)
{
	if (data[0] == '"') {
		int lastTokenIndex = data.lastIndexOf('"');
		data = data.mid(1, lastTokenIndex - 1);
		var = new GFDVarString();
		var->setValue(data);
		return true;
	} else if (data[0] == '[') {
		int lastTokenIndex = data.lastIndexOf(']');
		data = data.mid(1, lastTokenIndex - 1);
		var = new GFDVarArray();
		int index = indexOfToken(data);
		while (index != -1) {
			QString line =  data.left(index);
			GFDVar *newVar = nullptr;
			bool status;
			data.remove(0, index + 1);
			status = parseVar(newVar, line);
			if (!status) return false;
			var->addValue(newVar);
			index = indexOfToken(data);
		}
		return true;
	} else if (data[0] == '{') {
		int lastTokenIndex = data.lastIndexOf('}');
		data = data.mid(1, lastTokenIndex - 1);
		var = new GFDVarObject();
		bool status = parse(data,(GFDVarObject*)var);
		return status;
	} else if (data == "true") {
		var = new GFDVarBool();
		var->setValue(true);
		return true;
	} else if (data == "false") {
		var = new GFDVarBool();
		var->setValue(false);
		return true;
	} else {
		bool status;
		double doubleValue = data.toDouble(&status);
		int intValue = doubleValue;
		if (status) {
			if (doubleValue == intValue) {
				var = new GFDVarInt();
				var->setValue(intValue);
			} else {
				var = new GFDVarDouble();
				var->setValue(doubleValue);
			}
			return true;
		}
	}
	var = new GFDVar();
	return false;
}
