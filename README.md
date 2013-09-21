GFD
===

Game Format Date
Написано на Qt

Функционал как у json, проще в синтаксисе, массивы из разных типов элементов.

Пример использования:

содержимое filename.gfd<br>
integer = 2432.234;<br>
string = "Hello, world!";<br>
bool = true;<br>
array = [5,2,6,3,5];<br>
array1 = ["H","e","l","l","o"];<br>
array3 = [true,false];<br>
array4 = [5,"World", true];<br>
object = {<br>
  integer = 5345.23;<br>
  objectInObject = {<br>
    string = "Text";<br>
  };<br>
};<br>

\#include "mainwindow.h"<br>
\#include "gfd.h"<br>

int main(int argc, char *argv[])<br>
{<br>
  GFD config("filename.gfd") //открытие файла<br>
  <br>
  // берем параметры<br>
  double integer = config["integer"];<br>
  QString str = config["string"];<br>
  bool b = config["array4"][2];<br>
  double int1 = config["object"]["integer"];<br>
  QString txt = config["object"]["objectInObject"]["string"]<br>
  <br>
  
  qDebug() << integer << str << b << int1 << txt;<br>
  <br>
  return 0;<br>
}<br>
<br>
//////<br>
Получим:<br>
2432.234 Hello, world! true 5345.23 Text<br>
