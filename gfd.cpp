#include "gfd.h"

GFD::GFD(const QString &name, QObject *parent) :
	QObject(parent)
{
	QFile file(name);
	QString data;

	file.open(QFile::ReadOnly);
	data = file.readAll();
	file.close();
	bool status = parsing(data,this);
	if (status) {
		qDebug() << "Success";
	} else {
		qDebug() << "Fail";
	}

}

bool GFD::parsing(QString &data, GFDObject *object)
{
	int index = 0;


	while (index != -1) {

		index = indexOfToken(data);
		if (index != -1) {
			GFDVar *var = new GFDVar;
			QString line;
			QString varName;
			bool status;
			int index1;

			line = data.left(index);
			data.remove(0,index + 1);
			line = formatting(line);
			index1 = line.indexOf('=');
			varName = line.left(index1);
			var->setName(varName);
			line.remove(0,index1 + 1);
			status = parsValue(var, line);
			if (status) {
				object->addVar(var);
				continue;
			}
		} else {
			continue;
		}
		return false;
	}
	return true;
}

bool GFD::parsValue(GFDVar *var, QString &text)
{
	if (text[0] == '"') {
		int endIndex;

		var->setType(GFD_VAR_TYPE_STRING);
		endIndex = text.lastIndexOf('"');
		text = text.mid(1, endIndex - 1);
		var->setValue(text);
		qDebug() << "String" << text;
		return true;
	} else if (text[0] == '['){
		int endIndex;
		bool status;

		var->setType(GFD_VAR_TYPE_ARRAY);
		endIndex = text.lastIndexOf(']');
		text = text.mid(1, endIndex - 1);

		QStringList list;
		int index = indexOfToken(text);

		while (index != - 1) {
			list.append(text.left(index));
			text.remove(0,index + 1);
			index = indexOfToken(text);
		}

		for (int q = 0; q < list.size(); q++) {
			GFDVar *newVar = new GFDVar;
			status = parsValue(newVar, list[q]);
			if (!status) return false;
			var->addArrayValue(newVar);
		}
		return true;
	} else if (text[0] == '{') {
		int endIndex;

		var->setType(GFD_VAR_TYPE_OBJECT);
		endIndex = text.lastIndexOf('}');
		text = text.mid(1, endIndex - 1);
		GFDObject *newObject = new GFDObject;
		parsing(text, newObject);
		var->setValue(newObject);
		return true;
	}else if (text == "true") {
		var->setType(GFD_VAR_TYPE_BOOL);
		var->setValue(true);
		qDebug() << "Bool" << "true";
		return true;
	} else if (text == "false") {
		var->setType(GFD_VAR_TYPE_BOOL);
		var->setValue(false);
		qDebug() << "Bool" << "false";
		return true;
	} else {
		bool status;
		double value = text.toDouble(&status);

		if (status) {
			var->setType(GFD_VAR_TYPE_INT);
			var->setValue(value);
			qDebug() << "Int" << value;
			return true;
		}
	}
	return false;
}

QString GFD::formatting(const QString &text)
{
	bool textOpen = false;
	QString fText = text;
	for (int q = 0; q < fText.size(); q++) {
		if (fText[q] == '"') {
			textOpen = !textOpen;
		} else if (( fText[q] == ' ') & (!textOpen)) {
			fText.remove(q,1);
			q--;
		} else if ((fText[q] == '	') & (!textOpen)) {
			fText.remove(q,1);
			q--;
		} else if ((fText[q] == '\n') & (!textOpen)) {
			fText.remove(q,1);
			q--;
		}
	}
	return fText;
}

int GFD::indexOfToken(const QString &text)
{
	int index = -1;
	int openToken = 0;
	bool openText = false;

	for (int q = 0; q < text.size(); q++) {
		if (text[q] == '{') {
			openToken++;
		} else if (text[q] == '[') {
			openToken++;
		} else if (text[q] == '}') {
			openToken--;
		} else if (text[q] == ']') {
			openToken--;
		} else if (text[q] == '"') {
			openText = !openText;
		} else if ((text[q] == ';') & (!openText) & (openToken == 0)) {
			index = q;
			break;
		}
	}
	if ((index == -1) & (text.size() > 0)) {
		index = text.size() - 1;
	}
	return index;
}
