### TinyXML2

GitHub: https://github.com/leethomason/tinyxml2, документация онлайн: http://leethomason.github.io/tinyxml2/

Реально крошечная (всего 150 Кб) библиотечка для работы с XML, которую можно добавить в свой проект простым копированием. Требования к компилятору минимальные. API довольно интуитивный.

Допустим, у нас есть XML-файл document.xml следующего содержания:

```xml
<document>
  <data>1</data>
  <data>2</data>
  <data>3</data>
</document>
```

Вот как легко распарсить документ:

```c++
#include <iostream>
#include "tinyxml2.h"
 
int main ()
{
    tinyxml2::XMLDocument document;
    document.LoadFile ("document.xml");
    const auto root = document.RootElement();
    std::cout << root->Name() << std::endl;
    auto node = root->FirstChild()->ToElement();
    while (node) {
        std::cout << node->Name () << ": " << node->GetText () << std::endl;
        node = node->NextSiblingElement ();
    }
    return 0;
}
```

Библиотечка, состоящая из двух файлов — `tinyxml2.h` и `tinyxml2.cpp` — помещена в папку `tinyxml` в корне проекта. Настройка проекта тривиальна (`CMakeLists.txt`):

```cmake
cmake_minimum_required(VERSION 3.16)
project(learnXml)
set(CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR}/tinyxml)
add_library(tinyxml2 STATIC tinyxml/tinyxml2.cpp)
add_executable(learnXml main.cpp)
target_link_libraries(learnXml tinyxml2)
```

TinyXML2 предполагает, что кодировка XML-файлов UTF-8. Если это не так, надо как-то выкручиваться.

Как распарсить текст:

```c++
const char *text = "<root><element>1</element></root>";
tinyxml2::XMLDocument document;
document.Parse (text);
std::cout << document.RootElement()->Name() << std::endl;
```

Как сформировать документ:

```c++
tinyxml2::XMLDocument document;
auto root = document.NewElement ("root");
document.InsertEndChild(root);
auto element1 = root->InsertNewChildElement ("element1");
element1->SetAttribute ("attribute1", "value1");
auto element2 = root->InsertNewChildElement("element2");
element2->SetAttribute ("attribute2", "value2");
auto russian = root->InsertNewChildElement ("russian");
russian->SetText ("Некий русский текст");
document.SaveFile ("test.xml");
```

Формирует файл test.xml следующего содержания (UTF-8):

```xml
<root>
    <element1 attribute1="value1"/>
    <element2 attribute2="value2"/>
    <russian>Некий русский текст</russian>
</root>
```

Поддерживается простая навигация по элементам и атрибутам:

```c++
const auto foundElement = root->FirstChildElement ("element2");
const auto foundAttribute = foundElement->FindAttribute ("attribute2");
std::cout << foundAttribute->Value() << std::endl;
```
