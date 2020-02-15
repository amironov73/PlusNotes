### CMake

CMake -- это кроссплатформенная система автоматизации сборки программного обеспечения из исходного кода. CMake не занимается непосредственно сборкой, а лишь генерирует файлы управления сборкой из файлов CMakeLists.txt. Она выступает в качестве front-end, вызывая непосредственно используемую систему сборки (которая выступает в качестве back-end), так что конечный потребитель может считать, что CMake -- полноценная система сборки.

Официальный сайт: [cmake.org](https://cmake.org).

#### Hello world

Создадим пустую папку `HelloCMake`, а в ней два файла: `hello.cpp`

```c++
#include <iostream>

int main ()
{
  std::cout << "Hello, world!" << std::endl;
  return 0;
}
```

и `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 2.8)

project(hello)

add_executable(hello hello.cpp)
```

Теперь нам потребуется всего лишь две команды. Первая заставляет CMake сгенерировать проект для реальной системы сборки (на моём ноутбуке это Visual Studio 2019 Community Edition):

```
> cmake .

-- Building for: Visual Studio 16 2019
-- The C compiler identification is MSVC 19.24.28314.0
-- The CXX compiler identification is MSVC 19.24.28314.0
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Projects/HelloCMake
```

CMake создала подпапку `CMakeFiles` и горсть текстовых файлов в нашей папке: `hello.sln`, `hello.vcxproj` и др. Наша папка загаживается временными по сути файлами (ведь в любой момент CMake может создать их снова). Поэтому рекомендуется запускать CMake в какой-нибудь временной подпапке, например `build`:

```
> mkdir build
> cd build
> cmake ..

-- Building for: Visual Studio 16 2019
...
-- Build files have been written to: D:/Projects/HelloCMake/build
```

Теперь, когда файл проекта сгенерирован, можно выполнить сборку (всё ещё находясь в подпапке `build`):

```
> cmake --build .

Microsoft (R) Build Engine версии 16.4.0+e901037fe для .NET Framework
(C) Корпорация Майкрософт (Microsoft Corporation). Все права защищены.

  Checking Build System
  Building Custom Rule D:/Projects/HelloCMake/CMakeLists.txt
  hello.cpp
  hello.vcxproj -> D:\Projects\HelloCMake\build\Debug\hello.exe
  Building Custom Rule D:/Projects/HelloCMake/CMakeLists.txt
```

Если сборка проекта прошла успешно, мы можем забрать из папки `build/Debug` нужный нам файл `hello.exe`, а саму папку `build` удалить вместе со всеми подпапками.

Обратите внимание, мы сгенерировали проекты для отладочной сборки. Если нам нужен релизный билд, команда должна быть такая:

```
cmake -D CMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

Также обратите внимание, CMake сама догадалась, как правильно вызвать `MSBuild` для сборки проекта и передала ей все необходимые сведения. Точно так же она умеет сама вызывать `make`, `ninja` и другие системы сборки. От нас (в большинстве случаев) не требуется разбираться в тонкостях тулчейна, используемого на конкретной машине. Это очень важное свойство CMake. В большинстве случаев от нас требуется всего две команды:

```
> cmake ..
> cmake --build .
```

Главное -- не перепутать количество точек в первой и второй строке! :)

Вот схема зависимостей CMake, которую я взял из презентации ["Modern CMake / an Introduction"](https://docs.google.com/presentation/d/18fY0zDtJCMUW5WdY2ZOfKtvb7lXEbBPFe_I6MNJC0Qw):

![dependencies](img/cmake-1.png)

#### Настройка сборки

На моей машине, кроме Visual Studio 2019, установлена также Visual Studio 2015 Community Edition. Можно заставить CMake использовать для сборки именно её:

```
> cmake -G "Visual Studio 14 2015 Win64" ..

-- Selecting Windows SDK version 10.0.14393.0 to target Windows 10.0.17763.
-- The C compiler identification is MSVC 19.0.24215.1
-- The CXX compiler identification is MSVC 19.0.24215.1
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl.exe
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl.exe
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Projects/HelloCMake/build
```

Дополнительно можно указать необходимый [тулсет](Toolsets.md):

```
> cmake -G "Visual Studio 14 2015 Win64" -T v140 ..
```

На моём ноутбуке также установлен тулчейн MinGW-4.9 (для сборки QT-проектов). CMake легко можно заставить использовать его вместо Visual Studio (в примере ниже перевод строки добавлен для читабельности, в реальности его нет):

```
> set PATH=C:/Qt/5.6.3/mingw49_32/bin;C:/Qt/Tools/mingw492_32/bin

> cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ \ 
  -D CMAKE_MAKE_PROGRAM=mingw32-make -D CMAKE_BUILD_TYPE=Release ..

-- The C compiler identification is GNU 4.9.2
-- The CXX compiler identification is GNU 4.9.2
-- Check for working C compiler: C:/Qt/Tools/mingw492_32/bin/gcc.exe
-- Check for working C compiler: C:/Qt/Tools/mingw492_32/bin/gcc.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Qt/Tools/mingw492_32/bin/g++.exe
-- Check for working CXX compiler: C:/Qt/Tools/mingw492_32/bin/g++.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Projects/HelloCMake/build

> cmake --build . --config Release

Scanning dependencies of target hello
[ 50%] Building CXX object CMakeFiles/hello.dir/hello.cpp.obj
[100%] Linking CXX executable hello.exe
[100%] Built target hello
```

#### CMake GUI

В поставку CMake входит утилита CMakeGUI, позволяющая создать CMakeLists.txt в "мышинном режиме":

![cmake-gui-1](img/cmake-gui-1.png)

![cmake-gui-2](img/cmake-gui-2.png)

#### Настройка компилятора C++

```cmake
# Способ первый: затребовать от компилятора фичу cxx_std_17
target_compile_features(${TARGET} PUBLIC cxx_std_17)

# Способ второй: указать компилятору на стандарт
set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
```

#### Добавление исходных файлов "скопом", а не по одному

```cmake
project(irbis)

FILE(GLOB HeaderFiles *.h)
FILE(GLOB CppFiles *.cpp)

set(SOURCES ${CppFiles} ${HeaderFiles})

add_library(irbis SHARED ${SOURCES})
```

#### Подпроекты

CMake поддерживает сложную структуру вложенных проектов. Каждый подпроект оформляется как подпапка с соответствующим `CMakeLists.txt`, на который ссылается топовый `CMakeLists.txt`. Попробуем сделать для примера такую структуру:

* **SubLibrary1** — статическая библиотека, имеющая как библиотечный файл `.lib`, так и заголовочный файл `.h`;
* **SubLibrary2** — библиотека, состоящая из единственного заголовочного файла `.h`;
* **SubBinary** — приложение, использующее обе эти библиотеки.

Вот как оформляется эта структура на диске:

```
$ tree
.
├── CMakeLists.txt
├── SubBinary
│   ├── CMakeLists.txt
│   └── main.cpp
├── SubLibrary1
│   ├── CMakeLists.txt
│   ├── include
│   │   └── sublib1
│   │       └── sublib1.h
│   └── src
│       └── sublib1.cpp
└── SubLibrary2
    ├── CMakeLists.txt
    └── include
        └── sublib2
            └── sublib2.h
```

Содержимое этих файлов. Корневой CMakeLists.txt:

```cmake
cmake_minimum_required (VERSION 2.8)
 
project(MainProject)
 
add_subdirectory(SubLibrary1)
add_subdirectory(SubLibrary2)
add_subdirectory(SubBinary)
```

`SubBinary/CMakeLists.txt`:

```cmake
project(SubBinary)
 
# Create the executable
add_executable(${PROJECT_NAME} main.cpp)
 
# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    sub::lib1
    sub::lib2
)
```

`SubBinary/main.cpp`:

```c++
#include "sublib1/sublib1.h"
#include "sublib2/sublib2.h"
 
int main(int argc, char *argv[])
{
    sublib1 hi;
    hi.print();
 
    sublib2 howdy;
    howdy.print();
     
    return 0;
}
```

`SubLibrary1/CMakeLists.txt`:

```cmake
# Set the project name
project (SubLibrary1)
 
# Add a library with the above sources
add_library(${PROJECT_NAME} src/sublib1.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})
 
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
```

`SubLibrary1/include/sublib1/sublib1.h`:

```c++
#ifndef __SUBLIB_1_H__
#define __SUBLIB_1_H__
 
class sublib1
{
public:
    void print();
};
#endif
```

`SubLibrary1/src/sublib1.cpp`:

```c++
#include <iostream>
 
#include "sublib1/sublib1.h"
 
void sublib1::print()
{
    std::cout << "Hello sub-library 1!" << std::endl;
}
```

`SubLibrary2/CMakeLists.txt`:

```cmake
# Set the project name
project (SubLibrary2)
 
add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})
 
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
```

`SubLibrary2/include/sublib2/sublib2.h`:

```c++
#ifndef __SUBLIB_2_H__
#define __SUBLIB_2_H__
 
#include <iostream>
 
class sublib2
{
public:
    void print()
    {
        std::cout << "Hello header only sub-library 2!" << std::endl;
    }
};
 
#endif
```

Теперь попробуем собрать этот проект:

```
> mkdir build
> cd build
> cmake ..
-- Building for: Visual Studio 16 2019
-- The C compiler identification is MSVC 19.24.28315.0
-- The CXX compiler identification is MSVC 19.24.28315.0
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/Hostx64/x64/cl.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Temp/build
 
> cmake --build .
Microsoft (R) Build Engine версии 16.4.0+e901037fe для .NET Framework
(C) Корпорация Майкрософт (Microsoft Corporation). Все права защищены.
 
  Checking Build System
  Building Custom Rule D:/Temp/SubLibrary1/CMakeLists.txt
  sublib1.cpp
  SubLibrary1.vcxproj -> D:\Temp\build\SubLibrary1\Debug\SubLibrary1.lib
  Building Custom Rule D:/Temp/SubBinary/CMakeLists.txt
  main.cpp
  SubBinary.vcxproj -> D:\Temp\build\SubBinary\Debug\SubBinary.exe
  Building Custom Rule D:/Temp/CMakeLists.txt
 
> SubBinary/Debug/SubBinary.exe
Hello sub-library 1!
Hello header only sub-library 2!
```

Можно было и не заводить алиасы sub::lib1 и sub::lib2, без них проект тоже отлично собирается.

При определённой сноровке легко пишется многоуровневый проект с юнит-тестами и программистками 🙂:

```cmake
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
 
project(LearnCmake)
 
# where artifacts will be gathered
set(ARTIFACTS ${PROJECT_SOURCE_DIR}/artifacts)
 
# headers of third-party libraries
include_directories(${PROJECT_SOURCE_DIR}/third)
 
# subdirectories
add_subdirectory(libs)
add_subdirectory(tests)
add_subdirectory(apps)
 
# gather artifacts
install(TARGETS
    irbis
    hello
    safeTests
    onlineTests
    DESTINATION ${ARTIFACTS}
)
 
install(FILES
    ${irbis_SOURCE_DIR}/include/irbis.h
    ${something_SOURCE_DIR}/include/something.h
    DESTINATION ${ARTIFACTS}
)
```

И всё это дело компилируется/собирается/тестируется буквально в три строчки:

```shell script
#! /bin/sh
 
cmake -B ./build -D CMAKE_BUILD_TYPE=Release .
cmake --build ./build --config Release 
cmake --install ./build --config Release 
 
./artifacts/safeTests
```

#### Команды

https://cmake.org/cmake/help/v3.17/manual/cmake-commands.7.html

##### Команды скриптинга

* **break** – выход из цикла `foreach` или `while`;

* **cmake_host_system_information \(RESULT \<variable\> QUERY \<key\> …\)** – запрос информации о хосте, на котором производится сборка:

```cmake
cmake_host_system_information(RESULT vmem QUERY AVAILABLE_VIRTUAL_MEMORY)
message("Virtual memory = " ${vmem} " MB")
```
 
* **cmake_minimum_required \(VERSION \<min\>\[…\<max\>\] \[FATAL_ERROR\]\)** – указание необходимой версии CMake;

* **cmake_parse_arguments \(\<prefix\> \<options\> \<one_value_keywords\> \<multi_value_keywords\> \<args\> …\)** – команда для использования в макросах или функциях;

* **cmake_policy** – управление политиками;

* **configure_file \(\<input\> \<output\>\[COPYONLY\] \[ESCAPE_QUOTES\] \[@ONLY\] \[NEWLINE_STYLE \[UNIX|DOS|WIN32|LF|CRLF\] \]\)** – копирование файла с расширением переменных;

* **continue** – пропуск одной итерации в цикле `foreach` или `while`;

* **else** – ветка ИНАЧЕ в команде `if`;

* **elseif** – ветка ИНАЧЕ-ЕСЛИ в команде `if`;

* **endforeach** – закрывающая команда для `foreach`;

* **endfunction** – закрывающая команда для `function`;

* **endif** – закрывающая команда для `if`;

* **endmacro** – закрывающая команда для `macro`;

* **endwhile** – закрывающая команда для `while`;

* **execute_process** – запуск одного или более подпроцесса;

* **file** – манипуляции с файлами;

* **find_file** – поиск файла вообще \(получение полного пути к файлу, про который не известно точно, где он расположен\);

* **find_library** – поиск библиотеки;

* **find_package** – поиск пакета;

* **find_path** – поиск папки, содержащей указанный файл;

* **find_program** – поиск программы;

* **foreach** – цикл ДЛЯ:

```cmake
foreach(<loop_var> <items>)
  commands()
endforeach()
```

* **function** – определение функции:

```cmake
function(<name> [<arg1> ...])
  commands()
endfunction()
```

* **get_cmake_property** –

* **get_directory_property** –

* **get_filename_component** –

* **get_property** –

* **if** – условный оператор;

* **include \(\<file|module\> \[OPTIONAL\] \[RESULT_VARIABLE \<var\>\] \[NO_POLICY_SCOPE\]\)** – включение скрипта из указанного файла. Если указано `OPTIONAL`, то при отсутствии указанного файла ошибки не будет;

* **include_guard** –

* **list** –

* **macro** –

* **mark_as_advanced** –

* **math** –

* **message** –

* **option** –

* **return** –

* **separate_arguments** –

* **set** –

* **set_directory_properties** –

* **set_property** –

* **site_name** –

* **string** –

* **unset \(\<variable\> \[CACHE | PARENT_SCOPE\]\)** – удаление обычной переменной CMake. Для удаления переменной окружения `unset(ENV{<variable>})`;

* **variable_watch \(\<variable\> \[\<command\>\]\)** – отслеживать изменения переменной. Когда указанная переменная поменяет значение, будет выведено соответствующее сообщение, либо выполнена указанная команда;

* **while** – цикл ПОКА:

```cmake
while(<condition>)
  commands()
endwhile()
```

##### Команды проекта

* **add_compile_definitions** –

* **add_compile_options** –

* **add_custom_command** –

* **add_custom_target** –

* **add_definitions** –

* **add_dependencies** –

* **add_executable** –

* **add_library** –

* **add_link_options** –

* **add_subdirectory** –

* **add_test** –

* **aux_source_directory** –

* **build_command** –

* **create_test_sourcelist** –

* **define_property** –

* **enable_language** –

* **enable_testing** –

* **export** –

* **fltk_wrap_ui** –

* **get_source_file_property** –

* **get_target_property** –

* **get_test_property** –

* **include_directories** –

* **include_external_msproject** –

* **include_regular_expression** –

* **install** –

* **link_directories** –

* **link_libraries** –

* **load_cache** –

* **project** –

* **remove_definitions** –

* **set_source_files_properties** –

* **set_target_properties** –

* **set_tests_properties** –

* **source_group** –

* **target_compile_definitions** –

* **target_compile_features** –

* **target_compile_options** –

* **target_include_directories** –

* **target_link_directories** –

* **target_link_libraries** –

* **target_link_options** –

* **target_precompile_headers** –

* **target_sources** –

* **try_compile** –

* **try_run** –

##### CTest

* **ctest_build** –

* **ctest_configure** –

* **ctest_coverage** –

* **ctest_empty_binary_directory** –

* **ctest_memcheck** –

* **ctest_read_custom_files** –

* **ctest_run_script** —

* **ctest_sleep** –

* **ctest_start** –

* **ctest_submit** –

* **ctest_test** –

* **ctest_update** –

* **ctest_upload** –

#### Подключение внешних библиотек

```cmake
add_library(netutil STATIC IMPORTED)
set_property(TARGET netutil PROPERTY
            IMPORTED_LOCATION 
            Binary/game_client/libnetutil.a)
target_link_libraries(game netutil)
```

