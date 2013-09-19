GFD
===

Game Format Date
Написано на Qt

Функционал как у json, проще в синтаксисе, массивы из разных типов элементов.

Пример использования:

содержимое filename.gfd
integer = 2432.234;
string = "Hello, world!";
bool = true;
array = [5,2,6,3,5];
array1 = ["H","e","l","l","o"];
array3 = [true,false];
array4 = [5,"World", true];
object = {
  integer = 5345.23;
  objectInObject = {
    string = "Text";
  };
};

#include "mainwindow.h"
#include "gfd.h"

int main(int argc, char *argv[])
{
  GFD config("filename.gfd") //открытие файла
  
  // берем параметры
  double integer = config.getValue("integer")->getIntValue();
  QString str = config.getValue("string")->getStrValue();
  bool b = config.getValue("array4")->getArrayValue(2)->getBoolValue();
  double int1 = config.getValue("object")->getValue("integer")->getIntValue();
  QString txt = config.getValue("object")->getValue("objectInObject")->getValue("string")->getStrValue();
  
  qDebug() << integer << str << b << int1 << txt;
  
	return 0;
}

//////
Получим:
2432.234 Hello, world! true 5345.23 Text
