#include "gfd.h"

GFD::GFD(const QString &name, QObject *parent) :
	QObject(parent),
	_fileName(name)
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

GFD::GFD(QObject *parent):
	QObject(parent)
{
}

void GFD::save(QString fileName)
{
	if (fileName == "") {
		fileName = _fileName;
	}

	QFile file(fileName);
	QString data = "";

	file.open(QFile::WriteOnly);
	GFDVar *var = toVar();

	serializeObject(data, var, true);
	file.write(data.toLocal8Bit());
	file.close();
	delete var;

}

void GFD::serializeVar(QString &data, GFDVar *var, bool inArray)
{
	if (!inArray) {
		switch (var->getType()) {
			case GFD_VAR_TYPE_STRING: {
				data.append(QString("%1 = \"%2\";\n").arg(var->getName()).arg(var->toQString()));
				break;
			}
			case GFD_VAR_TYPE_INT: {
				data.append(QString("%1 = %2;\n").arg(var->getName()).arg(var->toDouble()));
				break;
			}
			case GFD_VAR_TYPE_BOOL: {
				QString boolStr;
				if (var->toBool()) {
					boolStr = "true";
				} else {
					boolStr = "false";
				}
				data.append(QString("%1 = %2;\n").arg(var->getName()).arg(boolStr));
				break;
			}
			case GFD_VAR_TYPE_ARRAY: {
				serializeArray(data, var);
				break;
			}
			case GFD_VAR_TYPE_OBJECT: {
				serializeObject(data, var);
				break;
			}
		}
	} else {
		switch (var->getType()) {
			case GFD_VAR_TYPE_STRING: {
				data.append(QString("\"%1\"; ").arg(var->toQString()));
				break;
			}
			case GFD_VAR_TYPE_INT: {
				data.append(QString("%1; ").arg(var->toDouble()));
				break;
			}
			case GFD_VAR_TYPE_BOOL: {
				QString boolStr;
				if (var->toBool()) {
					boolStr = "true";
				} else {
					boolStr = "false";
				}
				data.append(QString("%1; ").arg(boolStr));
				break;
			}
			case GFD_VAR_TYPE_ARRAY: {
				serializeArray(data, var);
				data.append(" ");
				break;
			}
			case GFD_VAR_TYPE_OBJECT: {
				data.append("\n");
				serializeObject(data, var);
				data.append("\n");
				break;
			}
		}
	}
}

void GFD::serializeObject(QString &data, GFDVar *var, bool isMain)
{
	if (!isMain) data.append(QString("%1 = {\n").arg(var->getName()));
	for (size_t q = 0; q < var->toObject()->getSize(); q++) {
		serializeVar(data, var->toObject()->getVar(q));
	}
	if (!isMain) data.append("};\n");
}

void GFD::serializeArray(QString &data, GFDVar *var)
{
	data.append(QString("%1 = ["));
	for (size_t q = 0; q < var->getArraySize(); q++) {
		serializeVar(data, var->getArrayVar(q), true);
	}
	data.append("];\n");
}

GFDVar *GFD::toVar()
{
	GFDVar *var = new GFDVar;
	var->setName("main");
	var->setValue(this);
	return var;
}

bool GFD::parsing(QString &data, GFDObject *object)
{
	int index = indexOfToken(data);


	while (index != -1) {
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
			}
		}
		index = indexOfToken(data);
	}
	return true;
}

bool GFD::parsValue(GFDVar *var, QString &text)
{
	if (text[0] == '"') {
		int endIndex;

		endIndex = text.lastIndexOf('"');
		text = text.mid(1, endIndex - 1);
		var->setValue(text);
		qDebug() << "String" << text;
		return true;
	} else if (text[0] == '['){
		int endIndex;
		bool status;

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
			GFDVar newVar;
			status = parsValue(&newVar, list[q]);
			if (!status) return false;
			var->addArrayValue(newVar);
		}
		return true;
	} else if (text[0] == '{') {
		int endIndex;

		endIndex = text.lastIndexOf('}');
		text = text.mid(1, endIndex - 1);
		GFDObject *newObject = new GFDObject;
		parsing(text, newObject);
		var->setValue(newObject);
		return true;
	}else if (text == "true") {
		var->setValue(true);
		qDebug() << "Bool" << "true";
		return true;
	} else if (text == "false") {
		var->setValue(false);
		qDebug() << "Bool" << "false";
		return true;
	} else {
		bool status;
		double value = text.toDouble(&status);

		if (status) {
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
		index = text.size();
	}
	return index;
}
