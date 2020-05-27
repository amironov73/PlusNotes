### Boost.DLL

Библотечка Boost.DLL позволяет загружать динамические библиотеки (файлы с расширениями DLL, SO и DYLIB) кроссплатформенным образом.

Пусть у нас есть очень сложная библиотечка математических функций:

```c
__declspec(dllexport) int adder (int x, int y)
{
    return x + y;
}
```

Настройка проекта DLL:

```cmake
cmake_minimum_required(VERSION 2.8)
project(supermath)
add_library(supermath SHARED supermath.c)
install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/artifacts)
```

Функции, в том числе `adder`, помещаются в `supermath.dll`. Вот как мы можем загрузить DLL и выполнить функцию `adder`: 

```c++
#include <iostream>
#include <boost/dll.hpp>

int main() 
{
    boost::dll::shared_library library ("supermath.dll");
    auto adder = library.get <int(int, int)> ("adder");
    const auto left = 120, right = 3;
    const auto result = adder (left, right);
    std::cout << left << " + " << right << " = " << result << std::endl;
    return 0;
}
```

Настройка проекта проста до наивности:

```cmake
cmake_minimum_required(VERSION 2.8)
project(client)
include_directories(C:/Boost)
link_directories(C:/Boost/stage/lib)
add_executable(client main.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/artifacts)
```

Кроме функций, можно получать доступ к статическим переменным, экспортированным из DLL:

```c++
int plugin_constant = lib.get <const int> ("integer_variable");
```
