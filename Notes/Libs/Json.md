### JSON for Modern C++

GitHub: [https://github.com/nlohmann/json](https://github.com/nlohmann/json), документация: [http://nlohmann.github.io/json/](http://nlohmann.github.io/json/).

Header-only библиотека, написанная на plain C++11, представляет собой один файл размером 800 Кб. Отличается поразительной легкостью освоения и интуитивно понятными проектными решениями (в основном). Вот, к примеру, как легко можно сформировать JSON-документ:

```c++
#include <iostream>
#include "nlohmann/json.hpp"
 
using nlohmann::json;
 
int main ()
{
    json j;
    j ["pi"] = 3.141;
    j ["happy"] = true;
    j ["name"] = "Niels";
    j ["nothing"] = nullptr;
    j ["answer"]["everything"] = 42;
    j ["list"] = { 1, 0, 2 };
    j ["object"] = { {"currency", "USD"}, {"value", 42.99} };
 
    std::cout << j.dump (2) << "\n";
 
    return 0;
}
```

выводит:

```json
{
  "answer": {
    "everything": 42
  },
  "happy": true,
  "list": [
    1,
    0,
    2
  ],
  "name": "Niels",
  "nothing": null,
  "object": {
    "currency": "USD",
    "value": 42.99
  },
  "pi": 3.141
}
```

Вся необходимая настройка умещается в одну строчку в `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(learnJson)
 
set(CMAKE_CXX_STANDARD 11)
 
include_directories(${PROJECT_SOURCE_DIR}/include)
 
add_executable(learnJson main.cpp)
```

Сформировать документ можно даже ещё проще:

```c++
#include <iostream>
#include "nlohmann/json.hpp"
 
using nlohmann::json;
 
int main ()
{
    json j =
    {
        { "pi", 3.141 },
        { "happy", true },
        { "name", "Niels" },
        { "nothing", nullptr },
        { "answer",
            {
                { "everything", 42 }
            }
        },
        { "list", { 1, 0, 2 } },
        { "object",
            {
                { "currency", "USD" },
                { "value", 42.99 }
            }
        }
    };
 
    std::cout << j.dump (2) << "\n";
 
    return 0;
}
```

Выводит, само собой, то же самое. Согласитесь, впечатляет.

Как распарсить текст:

```c++
std::string text = R"({"happy": true, "pi": 3.14})";
auto j = json::parse (text);
```

Есть ещё прикольный способ включения в программу JSON-литералов:

```c++
auto j = R"({"happy": true, "pi": 3.14})"_json;
```

Как добраться до нужных нам значений:

```c++
auto happy = j ["happy"].get <bool> ();
auto pi = j ["pi"].get <double> ();
std::cout << happy << ", " << pi << std::endl;
```

Работают итераторы:

```c++
// Создаем документ:
// [{"one": 1}, {"two", 2}, {"three", 3}]

auto j = json::array
    ({
        {{"one", 1}},
        {{"two", 2}},
        {{"three", 3}}
    });
 
for (const auto &item : j) {
    std::cout << item << std::endl;
}
```

напечатает

```
{"one":1}
{"two":2}
{"three":3}
```

Не совсем тривиально, но можно достучаться до ключей и значений объектов:

```c++
auto j = json::array
    ({
        {{"one", 1}},
        {{"two", 2}},
        {{"three", 3}}
    });
 
for (auto it = j.begin(); it != j.end(); ++it) {
    const json &value = it.value();
    if (value.is_object ()) {
        const auto inner = value.begin();
        std::cout << inner.key() << ": " << inner.value() << std::endl;
    }
}
```

выведет:

```
one: 1
two: 2
three: 3
```
