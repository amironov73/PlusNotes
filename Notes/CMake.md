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

  | Key                       | Description
  |---------------------------|------------------------
  | NUMBER_OF_LOGICAL_CORES   | Number of logical cores
  | NUMBER_OF_PHYSICAL_CORES  | Number of physical cores
  | HOSTNAME                  | Hostname
  | FQDN                      | Fully qualified domain name
  | TOTAL_VIRTUAL_MEMORY      | Total virtual memory in MiB
  | AVAILABLE_VIRTUAL_MEMORY  | Available virtual memory in MiB
  | TOTAL_PHYSICAL_MEMORY     | Total physical memory in MiB
  | AVAILABLE_PHYSICAL_MEMORY | Available physical memory in MiB
  | IS_64BIT                  | One if processor is 64Bit 
  | HAS_FPU                   | One if processor has floating point unit
  | HAS_MMX                   | One if processor supports MMX instructions
  | HAS_MMX_PLUS              | One if processor supports Ext. MMX instructions
  | HAS_SSE                   | One if processor supports SSE instructions
  | HAS_SSE2                  | One if processor supports SSE2 instructions
  | HAS_SSE_FP                | One if processor supports SSE FP instructions
  | HAS_SSE_MMX               | One if processor supports SSE MMX instructions
  | HAS_AMD_3DNOW             | One if processor supports 3DNow instructions
  | HAS_AMD_3DNOW_PLUS        | One if processor supports 3DNow+ instructions
  | HAS_IA64                  | One if IA64 processor emulating x86
  | HAS_SERIAL_NUMBER         | One if processor has serial number
  | PROCESSOR_SERIAL_NUMBER   | Processor serial number
  | PROCESSOR_NAME            | Human readable processor name
  | PROCESSOR_DESCRIPTION     | Human readable full processor description
  | OS_NAME                   | See CMAKE_HOST_SYSTEM_NAME
  | OS_RELEASE                | The OS sub-type e.g. on Windows Professional
  | OS_VERSION                | The OS build ID
  | OS_PLATFORM               | See CMAKE_HOST_SYSTEM_PROCESSOR

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

#### Переменные

https://cmake.org/cmake/help/v3.17/manual/cmake-variables.7.html

##### Информация о среде

* **CMAKE_ARGC** – количество аргументов командной строки в скриптовом режиме \(-P\);
* **CMAKE_ARGV0** – первый аргумент командной строки в скриптовом режиме (-P). Аналогично CMAKE_ARGV1, CMAKE_ARGV2 и т. д.;
* **CMAKE_BINARY_DIR** – путь к высшему уровню в дереве  сборки;
* **CMAKE_COMMAND** – полный путь к CMake.exe;
* **CMAKE_CURRENT_BINARY_DIR** – путь к текущей обрабатываемой папке;
* **CMAKE_CURRENT_LIST_DIR** – полная папка текущего обрабатываемого CMakeListst.txt;
* **CMAKE_CURRENT_LIST_FILE** –
* **CMAKE_CURRENT_LIST_LINE** –
* **CMAKE_CURRENT_SOURCE_DIR** - 
* **CMAKE_DEBUG_TARGET_PROPERTIES** —
* **CMAKE_DIRECTORY_LABELS** —
* **CMAKE_DL_LIBS** —
* **CMAKE_DOTNET_TARGET_FRAMEWORK** —
* **CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION** —
* **CMAKE_EDIT_COMMAND** —
* **CMAKE_EXECUTABLE_SUFFIX** —
* **CMAKE_EXTRA_GENERATOR** —
* **CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES** —
* **CMAKE_FIND_DEBUG_MODE** —
* **CMAKE_FIND_PACKAGE_NAME** —
* **CMAKE_FIND_PACKAGE_SORT_DIRECTION** —
* **CMAKE_FIND_PACKAGE_SORT_ORDER** —
* **CMAKE_GENERATOR** —
* **CMAKE_GENERATOR_INSTANCE** —
* **CMAKE_GENERATOR_PLATFORM** —
* **CMAKE_GENERATOR_TOOLSET** —
* **CMAKE_IMPORT_LIBRARY_PREFIX** —
* **CMAKE_IMPORT_LIBRARY_SUFFIX** —
* **CMAKE_JOB_POOL_COMPILE** —
* **CMAKE_JOB_POOL_LINK** —
* **CMAKE_JOB_POOL_PRECOMPILE_HEADER** —
* **CMAKE_JOB_POOLS** —
* **CMAKE_\<LANG\>_COMPILER_AR** —
* **CMAKE_\<LANG\>_COMPILER_RANLIB** —
* **CMAKE_\<LANG\>_LINK_LIBRARY_SUFFIX** —
* **CMAKE_LINK_LIBRARY_SUFFIX** —
* **CMAKE_LINK_SEARCH_END_STATIC** —
* **CMAKE_LINK_SEARCH_START_STATIC** —
* **CMAKE_MAJOR_VERSION** —
* **CMAKE_MAKE_PROGRAM** —
* **CMAKE_MATCH_COUNT** —
* **CMAKE_MATCH_\<n\>** —
* **CMAKE_MINIMUM_REQUIRED_VERSION** —
* **CMAKE_MINOR_VERSION** —
* **CMAKE_NETRC** —
* **CMAKE_NETRC_FILE** —
* **CMAKE_PARENT_LIST_FILE** —
* **CMAKE_PATCH_VERSION** —
* **CMAKE_PROJECT_DESCRIPTION** —
* **CMAKE_PROJECT_HOMEPAGE_URL** —
* **CMAKE_PROJECT_NAME** —
* **CMAKE_PROJECT_VERSION** —
* **CMAKE_PROJECT_VERSION_MAJOR** —
* **CMAKE_PROJECT_VERSION_MINOR** —
* **CMAKE_PROJECT_VERSION_PATCH** —
* **CMAKE_PROJECT_VERSION_TWEAK** —
* **CMAKE_RANLIB** —
* **CMAKE_ROOT** —
* **CMAKE_RULE_MESSAGES** —
* **CMAKE_SCRIPT_MODE_FILE** —
* **CMAKE_SHARED_LIBRARY_PREFIX** —
* **CMAKE_SHARED_LIBRARY_SUFFIX** —
* **CMAKE_SHARED_MODULE_PREFIX** —
* **CMAKE_SHARED_MODULE_SUFFIX** —
* **CMAKE_SIZEOF_VOID_P** —
* **CMAKE_SKIP_INSTALL_RULES** —
* **CMAKE_SKIP_RPATH** —
* **CMAKE_SOURCE_DIR** —
* **CMAKE_STATIC_LIBRARY_PREFIX** —
* **CMAKE_STATIC_LIBRARY_SUFFIX** —
* **CMAKE_Swift_MODULE_DIRECTORY** —
* **CMAKE_Swift_NUM_THREADS** —
* **CMAKE_TOOLCHAIN_FILE** —
* **CMAKE_TWEAK_VERSION** —
* **CMAKE_VERBOSE_MAKEFILE** —
* **CMAKE_VERSION** —
* **CMAKE_VS_DEVENV_COMMAND** —
* **CMAKE_VS_MSBUILD_COMMAND** —
* **CMAKE_VS_NsightTegra_VERSION** —
* **CMAKE_VS_PLATFORM_NAME** —
* **CMAKE_VS_PLATFORM_NAME_DEFAULT** —
* **CMAKE_VS_PLATFORM_TOOLSET** —
* **CMAKE_VS_PLATFORM_TOOLSET_CUDA** —
* **CMAKE_VS_PLATFORM_TOOLSET_CUDA_CUSTOM_DIR** —
* **CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE** —
* **CMAKE_VS_PLATFORM_TOOLSET_VERSION** —
* **CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION** —
* **CMAKE_XCODE_GENERATE_SCHEME** —
* **CMAKE_XCODE_PLATFORM_TOOLSET** —
* **\<PROJECT-NAME\>_BINARY_DIR** —
* **\<PROJECT-NAME\>_DESCRIPTION** —
* **\<PROJECT-NAME\>_HOMEPAGE_URL** —
* **\<PROJECT-NAME\>_SOURCE_DIR** —
* **\<PROJECT-NAME\>_VERSION** —
* **\<PROJECT-NAME\>_VERSION_MAJOR** —
* **\<PROJECT-NAME\>_VERSION_MINOR** —
* **\<PROJECT-NAME\>_VERSION_PATCH** —
* **\<PROJECT-NAME\>_VERSION_TWEAK** —
* **PROJECT_BINARY_DIR** —
* **PROJECT_DESCRIPTION** —
* **PROJECT_HOMEPAGE_URL** —
* **PROJECT_NAME** —
* **PROJECT_SOURCE_DIR** —
* **PROJECT_VERSION** —
* **PROJECT_VERSION_MAJOR** —
* **PROJECT_VERSION_MINOR** —
* **PROJECT_VERSION_PATCH** —
* **PROJECT_VERSION_TWEAK** —

##### Изменение поведения

* **BUILD_SHARED_LIBS** —
* **CMAKE_ABSOLUTE_DESTINATION_FILES** —
* **CMAKE_APPBUNDLE_PATH** —
* **CMAKE_AUTOMOC_RELAXED_MODE** —
* **CMAKE_BACKWARDS_COMPATIBILITY** —
* **CMAKE_BUILD_TYPE** —
* **CMAKE_CODEBLOCKS_COMPILER_ID** —
* **CMAKE_CODEBLOCKS_EXCLUDE_EXTERNAL_FILES** —
* **CMAKE_CODELITE_USE_TARGETS** —
* **CMAKE_COLOR_MAKEFILE** —
* **CMAKE_CONFIGURATION_TYPES** —
* **CMAKE_DEPENDS_IN_PROJECT_ONLY** —
* **CMAKE_DISABLE_FIND_PACKAGE_\<PackageName\>** —
* **CMAKE_ECLIPSE_GENERATE_LINKED_RESOURCES** —
* **CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT** —
* **CMAKE_ECLIPSE_MAKE_ARGUMENTS** —
* **CMAKE_ECLIPSE_RESOURCE_ENCODING** —
* **CMAKE_ECLIPSE_VERSION** —
* **CMAKE_ERROR_DEPRECATED** —
* **CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION** —
* **CMAKE_EXECUTE_PROCESS_COMMAND_ECHO** —
* **CMAKE_EXPORT_COMPILE_COMMANDS** —
* **CMAKE_EXPORT_PACKAGE_REGISTRY** —
* **CMAKE_EXPORT_NO_PACKAGE_REGISTRY** —
* **CMAKE_FIND_APPBUNDLE** —
* **CMAKE_FIND_FRAMEWORK** —
* **CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX** —
* **CMAKE_FIND_LIBRARY_PREFIXES** —
* **CMAKE_FIND_LIBRARY_SUFFIXES** —
* **CMAKE_FIND_NO_INSTALL_PREFIX** —
* **CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY** —
* **CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY** —
* **CMAKE_FIND_PACKAGE_PREFER_CONFIG** —
* **CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS** —
* **CMAKE_FIND_PACKAGE_WARN_NO_MODULE** —
* **CMAKE_FIND_ROOT_PATH** —
* **CMAKE_FIND_ROOT_PATH_MODE_INCLUDE** —
* **CMAKE_FIND_ROOT_PATH_MODE_LIBRARY** —
* **CMAKE_FIND_ROOT_PATH_MODE_PACKAGE** —
* **CMAKE_FIND_ROOT_PATH_MODE_PROGRAM** —
* **CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH** —
* **CMAKE_FIND_USE_CMAKE_PATH** —
* **CMAKE_FIND_USE_CMAKE_SYSTEM_PATH** —
* **CMAKE_FIND_USE_PACKAGE_REGISTRY** —
* **CMAKE_FIND_USE_PACKAGE_ROOT_PATH** —
* **CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH** —
* **CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY** —
* **CMAKE_FRAMEWORK_PATH** —
* **CMAKE_IGNORE_PATH** —
* **CMAKE_INCLUDE_DIRECTORIES_BEFORE** —
* **CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE** —
* **CMAKE_INCLUDE_PATH** —
* **CMAKE_INSTALL_DEFAULT_COMPONENT_NAME** —
* **CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS** —
* **CMAKE_INSTALL_MESSAGE** —
* **CMAKE_INSTALL_PREFIX** —
* **CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT** —
* **CMAKE_LIBRARY_PATH** —
* **CMAKE_LINK_DIRECTORIES_BEFORE** —
* **CMAKE_MFC_FLAG** —
* **CMAKE_MAXIMUM_RECURSION_DEPTH** —
* **CMAKE_MESSAGE_CONTEXT** —
* **CMAKE_MESSAGE_CONTEXT_SHOW** —
* **CMAKE_MESSAGE_INDENT** —
* **CMAKE_MESSAGE_LOG_LEVEL** —
* **CMAKE_MODULE_PATH** —
* **CMAKE_POLICY_DEFAULT_CMP\<NNNN\>** —
* **CMAKE_POLICY_WARNING_CMP\<NNNN\>** —
* **CMAKE_PREFIX_PATH** —
* **CMAKE_PROGRAM_PATH** —
* **CMAKE_PROJECT_INCLUDE** —
* **CMAKE_PROJECT_INCLUDE_BEFORE** —
* **CMAKE_PROJECT_\<PROJECT-NAME\>_INCLUDE** —
* **CMAKE_PROJECT_\<PROJECT-NAME\>_INCLUDE_BEFORE** —
* **CMAKE_SKIP_INSTALL_ALL_DEPENDENCY** —
* **CMAKE_STAGING_PREFIX** —
* **CMAKE_SUBLIME_TEXT_2_ENV_SETTINGS** —
* **CMAKE_SUBLIME_TEXT_2_EXCLUDE_BUILD_TREE** —
* **CMAKE_SUPPRESS_REGENERATION** —
* **CMAKE_SYSROOT** —
* **CMAKE_SYSROOT_COMPILE** —
* **CMAKE_SYSROOT_LINK** —
* **CMAKE_SYSTEM_APPBUNDLE_PATH** —
* **CMAKE_SYSTEM_FRAMEWORK_PATH** —
* **CMAKE_SYSTEM_IGNORE_PATH** —
* **CMAKE_SYSTEM_INCLUDE_PATH** —
* **CMAKE_SYSTEM_LIBRARY_PATH** —
* **CMAKE_SYSTEM_PREFIX_PATH** —
* **CMAKE_SYSTEM_PROGRAM_PATH** —
* **CMAKE_USER_MAKE_RULES_OVERRIDE** —
* **CMAKE_WARN_DEPRECATED** —
* **CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION** —
* **CMAKE_XCODE_GENERATE_TOP_LEVEL_PROJECT_ONLY** —
* **CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER** —
* **CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN** —
* **CMAKE_XCODE_SCHEME_WORKING_DIRECTORY** —
* **CMAKE_XCODE_SCHEME_DEBUG_DOCUMENT_VERSIONING** —
* **CMAKE_XCODE_SCHEME_DISABLE_MAIN_THREAD_CHECKER** —
* **CMAKE_XCODE_SCHEME_DYNAMIC_LIBRARY_LOADS** —
* **CMAKE_XCODE_SCHEME_DYNAMIC_LINKER_API_USAGE** —
* **CMAKE_XCODE_SCHEME_ENVIRONMENT** —
* **CMAKE_XCODE_SCHEME_GUARD_MALLOC** —
* **CMAKE_XCODE_SCHEME_MAIN_THREAD_CHECKER_STOP** —
* **CMAKE_XCODE_SCHEME_MALLOC_GUARD_EDGES** —
* **CMAKE_XCODE_SCHEME_MALLOC_SCRIBBLE** —
* **CMAKE_XCODE_SCHEME_MALLOC_STACK** —
* **CMAKE_XCODE_SCHEME_THREAD_SANITIZER** —
* **CMAKE_XCODE_SCHEME_THREAD_SANITIZER_STOP** —
* **CMAKE_XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER** —
* **CMAKE_XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER_STOP** —
* **CMAKE_XCODE_SCHEME_ZOMBIE_OBJECTS** —
* **\<PackageName\>_ROOT** —

##### Описание системы

* **ANDROID** – устанавливается в 1, если система назначения `(CMAKE_SYSTEM_NAME)` Android;
* **APPLE** – устанавливается в true, если система назначения Apple: Mac OS, iOS, tvOS или watchOS;
* **BORLAND** – устанавливается в true для компиляторов BORLAND;
* **CMAKE_HOST_APPLE** – устанавливается в true, если компиляция происходит на Mac OS;
* **CMAKE_HOST_SOLARIS** — устанавливается в true, если компиляция происходит на Oracle Solaris;
* **CMAKE_HOST_SYSTEM** —
* **CMAKE_HOST_SYSTEM_NAME** —
* **CMAKE_HOST_SYSTEM_PROCESSOR** —
* **CMAKE_HOST_SYSTEM_VERSION** —
* **CMAKE_HOST_UNIX** —
* **CMAKE_HOST_WIN32** —
* **CMAKE_LIBRARY_ARCHITECTURE** —
* **CMAKE_LIBRARY_ARCHITECTURE_REGEX** —
* **CMAKE_OBJECT_PATH_MAX** —
* **CMAKE_SYSTEM** —
* **CMAKE_SYSTEM_NAME** —
* **CMAKE_SYSTEM_PROCESSOR** —
* **CMAKE_SYSTEM_VERSION** —
* **CYGWIN** —
* **GHS-MULTI** —
* **IOS** —
* **MINGW** —
* **MSVC** —
* **MSVC10, MSVC11, MSVC12, MSVC14, MSVC60, MSVC60, MSVC70, MSVC71, MSVC80, MSVC90** —
* **MSVC_IDE** —
* **MSVC_TOOLSET_VERSION** —
* **MSYS** —
* **UNIX** —
* **WIN32** —
* **WINCE** —
* **WINDOWS_PHONE** —
* **WINDOWS_STORE** —
* **XCODE** —
* **XCODE_VERSION** —

##### Контроль сборки

* **CMAKE_ANDROID_API** —
* **CMAKE_ANDROID_ANT_ADDITIONAL_OPTIONS** —
* **CMAKE_ANDROID_API** —
* **CMAKE_ANDROID_API_MIN** —
* **CMAKE_ANDROID_ARCH** —
* **CMAKE_ANDROID_ARCH_ABI** —
* **CMAKE_ANDROID_ARM_MODE** —
* **CMAKE_ANDROID_ARM_NEON** —
* **CMAKE_ANDROID_ASSETS_DIRECTORIES** —
* **CMAKE_ANDROID_GUI** —
* **CMAKE_ANDROID_JAR_DEPENDENCIES** —
* **CMAKE_ANDROID_JAR_DIRECTORIES** —
* **CMAKE_ANDROID_JAVA_SOURCE_DIR** —
* **CMAKE_ANDROID_NATIVE_LIB_DEPENDENCIES** —
* **CMAKE_ANDROID_NATIVE_LIB_DIRECTORIES** —
* **CMAKE_ANDROID_NDK** —
* **CMAKE_ANDROID_NDK_DEPRECATED_HEADERS** —
* **CMAKE_ANDROID_NDK_TOOLCHAIN_HOST_TAG** —
* **CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION** —
* **CMAKE_ANDROID_PROCESS_MAX** —
* **CMAKE_ANDROID_PROGUARD** —
* **CMAKE_ANDROID_PROGUARD_CONFIG_PATH** —
* **CMAKE_ANDROID_SECURE_PROPS_PATH** —
* **CMAKE_ANDROID_SKIP_ANT_STEP** —
* **CMAKE_ANDROID_STANDALONE_TOOLCHAIN** —
* **CMAKE_ANDROID_STL_TYPE** —
* **CMAKE_ARCHIVE_OUTPUT_DIRECTORY** —
* **CMAKE_ARCHIVE_OUTPUT_DIRECTORY_\<CONFIG\>** —
* **CMAKE_AUTOGEN_ORIGIN_DEPENDS** —
* **CMAKE_AUTOGEN_PARALLEL** —
* **CMAKE_AUTOGEN_VERBOSE** —
* **CMAKE_AUTOMOC** —
* **CMAKE_AUTOMOC_COMPILER_PREDEFINES** —
* **CMAKE_AUTOMOC_DEPEND_FILTERS** —
* **CMAKE_AUTOMOC_MACRO_NAMES** —
* **CMAKE_AUTOMOC_MOC_OPTIONS** —
* **CMAKE_AUTOMOC_PATH_PREFIX** —
* **CMAKE_AUTORCC** —
* **CMAKE_AUTORCC_OPTIONS** —
* **CMAKE_AUTOUIC** —
* **CMAKE_AUTOUIC_OPTIONS** —
* **CMAKE_AUTOUIC_SEARCH_PATHS** —
* **CMAKE_BUILD_RPATH** —
* **CMAKE_BUILD_RPATH_USE_ORIGIN** —
* **CMAKE_BUILD_WITH_INSTALL_NAME_DIR** —
* **CMAKE_BUILD_WITH_INSTALL_RPATH** —
* **CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY** —
* **CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY_\<CONFIG\>** —
* **CMAKE_\<CONFIG\>_POSTFIX** —
* **CMAKE_CTEST_ARGUMENTS** —
* **CMAKE_CUDA_SEPARABLE_COMPILATION** —
* **CMAKE_CUDA_RESOLVE_DEVICE_SYMBOLS** —
* **CMAKE_CUDA_RUNTIME_LIBRARY** —
* **CMAKE_DEBUG_POSTFIX** —
* **CMAKE_DISABLE_PRECOMPILE_HEADERS** —
* **CMAKE_ENABLE_EXPORTS** —
* **CMAKE_EXE_LINKER_FLAGS** —
* **CMAKE_EXE_LINKER_FLAGS_\<CONFIG\>** —
* **CMAKE_EXE_LINKER_FLAGS_\<CONFIG\>_INIT** —
* **CMAKE_EXE_LINKER_FLAGS_INIT** —
* **CMAKE_FOLDER** —
* **CMAKE_FRAMEWORK** —
* **CMAKE_Fortran_FORMAT** —
* **CMAKE_Fortran_MODULE_DIRECTORY** —
* **CMAKE_GHS_NO_SOURCE_GROUP_FILE** —
* **CMAKE_GLOBAL_AUTOGEN_TARGET** —
* **CMAKE_GLOBAL_AUTOGEN_TARGET_NAME** —
* **CMAKE_GLOBAL_AUTORCC_TARGET** —
* **CMAKE_GLOBAL_AUTORCC_TARGET_NAME** —
* **CMAKE_GNUtoMS** —
* **CMAKE_INCLUDE_CURRENT_DIR** —
* **CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE** —
* **CMAKE_INSTALL_NAME_DIR** —
* **CMAKE_INSTALL_REMOVE_ENVIRONMENT_RPATH** —
* **CMAKE_INSTALL_RPATH** —
* **CMAKE_INSTALL_RPATH_USE_LINK_PATH** —
* **CMAKE_INTERPROCEDURAL_OPTIMIZATION** —
* **CMAKE_INTERPROCEDURAL_OPTIMIZATION_\<CONFIG\>** —
* **CMAKE_IOS_INSTALL_COMBINED** —
* **CMAKE_\<LANG\>_CLANG_TIDY** —
* **CMAKE_\<LANG\>_COMPILER_LAUNCHER** —
* **CMAKE_\<LANG\>_CPPCHECK** —
* **CMAKE_\<LANG\>_CPPLINT** —
* **CMAKE_\<LANG\>_INCLUDE_WHAT_YOU_USE** —
* **CMAKE_\<LANG\>_LINK_LIBRARY_FILE_FLAG** —
* **CMAKE_\<LANG\>_LINK_LIBRARY_FLAG** —
* **CMAKE_\<LANG\>_VISIBILITY_PRESET** —
* **CMAKE_LIBRARY_OUTPUT_DIRECTORY** —
* **CMAKE_LIBRARY_OUTPUT_DIRECTORY_\<CONFIG\>** —
* **CMAKE_LIBRARY_PATH_FLAG** —
* **CMAKE_LINK_DEF_FILE_FLAG** —
* **CMAKE_LINK_DEPENDS_NO_SHARED** —
* **CMAKE_LINK_INTERFACE_LIBRARIES** —
* **CMAKE_LINK_LIBRARY_FILE_FLAG** —
* **CMAKE_LINK_LIBRARY_FLAG** —
* **CMAKE_LINK_WHAT_YOU_USE** —
* **CMAKE_MACOSX_BUNDLE** —
* **CMAKE_MACOSX_RPATH** —
* **CMAKE_MAP_IMPORTED_CONFIG_\<CONFIG\>** —
* **CMAKE_MODULE_LINKER_FLAGS** —
* **CMAKE_MODULE_LINKER_FLAGS_\<CONFIG\>** —
* **CMAKE_MODULE_LINKER_FLAGS_\<CONFIG\>_INIT** —
* **CMAKE_MODULE_LINKER_FLAGS_INIT** —
* **CMAKE_MSVCIDE_RUN_PATH** —
* **CMAKE_MSVC_RUNTIME_LIBRARY** —
* **CMAKE_NMC_CROSS_CONFIGS** —
* **CMAKE_NMC_DEFAULT_BUILD_FILE_CONFIG** —
* **CMAKE_NMC_DEFAULT_CONFIGS** —
* **CMAKE_NINJA_OUTPUT_PATH_PREFIX** —
* **CMAKE_NO_BUILTIN_CHRPATH** —
* **CMAKE_NO_SYSTEM_FROM_IMPORTED** —
* **CMAKE_OSX_ARCHITECTURES** —
* **CMAKE_OSX_DEPLOYMENT_TARGET** —
* **CMAKE_OSX_SYSROOT** —
* **CMAKE_PDB_OUTPUT_DIRECTORY** —
* **CMAKE_PDB_OUTPUT_DIRECTORY_\<CONFIG\>** —
* **CMAKE_POSITION_INDEPENDENT_CODE** —
* **CMAKE_RUNTIME_OUTPUT_DIRECTORY** —
* **CMAKE_RUNTIME_OUTPUT_DIRECTORY_\<CONFIG\>** —
* **CMAKE_SHARED_LINKER_FLAGS** —
* **CMAKE_SHARED_LINKER_FLAGS_\<CONFIG\>** —
* **CMAKE_SHARED_LINKER_FLAGS_\<CONFIG\>_INIT** —
* **CMAKE_SHARED_LINKER_FLAGS_INIT** —
* **CMAKE_SKIP_BUILD_RPATH** —
* **CMAKE_SKIP_INSTALL_RPATH** —
* **CMAKE_STATIC_LINKER_FLAGS** —
* **CMAKE_STATIC_LINKER_FLAGS_\<CONFIG\>** —
* **CMAKE_STATIC_LINKER_FLAGS_\<CONFIG\>_INIT** —
* **CMAKE_STATIC_LINKER_FLAGS_INIT** —
* **CMAKE_TRY_COMPILE_CONFIGURATION** —
* **CMAKE_TRY_COMPILE_PLATFORM_VARIABLES** —
* **CMAKE_TRY_COMPILE_TARGET_TYPE** —
* **CMAKE_UNITY_BUILD** —
* **CMAKE_UNITY_BUILD_BATCH_SIZE** —
* **CMAKE_USE_RELATIVE_PATHS** —
* **CMAKE_VISIBILITY_INLINES_HIDDEN** —
* **CMAKE_VS_GLOBALS** —
* **CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD** —
* **CMAKE_VS_INCLUDE_PACKAGE_TO_DEFAULT_BUILD** —
* **CMAKE_VS_JUST_MY_CODE_DEBUGGING** —
* **CMAKE_VS_SDK_EXCLUDE_DIRECTORIES** —
* **CMAKE_VS_SDK_EXECUTABLE_DIRECTORIES** —
* **CMAKE_VS_SDK_INCLUDE_DIRECTORIES** —
* **CMAKE_VS_SDK_LIBRARY_DIRECTORIES** —
* **CMAKE_VS_SDK_LIBRARY_WINRT_DIRECTORIES** —
* **CMAKE_VS_SDK_REFERENCE_DIRECTORIES** —
* **CMAKE_VS_SDK_SOURCE_DIRECTORIES** —
* **CMAKE_VS_WINRT_BY_DEFAULT** —
* **CMAKE_WIN32_EXECUTABLE** —
* **CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS** —
* **CMAKE_XCODE_ATTRIBUTE_\<an-attribute\>** —
* **EXECUTABLE_OUTPUT_PATH** —
* **LIBRARY_OUTPUT_PATH** —

##### Языки

* **CMAKE_COMPILER_IS_GNUCC** –
* **CMAKE_COMPILER_IS_GNUCXX** –
* **CMAKE_COMPILER_IS_GNUG77** –
* **CMAKE_CUDA_COMPILE_FEATURES** –
* **CMAKE_CUDA_HOST_COMPILER** –
* **CMAKE_CUDA_EXTENSIONS** –
* **CMAKE_CUDA_STANDARD** –
* **CMAKE_CUDA_STANDARD_REQUIRED** –
* **CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES** –
* **CMAKE_CXX_COMPILE_FEATURES** –
* **CMAKE_CXX_EXTENSIONS** –
* **CMAKE_CXX_STANDARD** –
* **CMAKE_CXX_STANDARD_REQUIRED** –
* **CMAKE_C_COMPILE_FEATURES** –
* **CMAKE_C_EXTENSIONS** –
* **CMAKE_C_STANDARD** –
* **CMAKE_C_STANDARD_REQUIRED** –

##### CTest

##### CPack

#### Переменные окружения

##### Контроль сборки

* **CMAKE_BUILD_PARALLEL_LEVEL** –
* **CMAKE_CONFIG_TYPE** –
* **CMAKE_EXPORT_COMPILE_COMMANDS** –
* **CMAKE_GENERATOR** –
* **CMAKE_GENERATOR_INSTANCE** –
* **CMAKE_GENERATOR_PLATFORM** –
* **CMAKE_GENERATOR_TOOLSET** -
* **CMAKE_\<LANG\>_COMPILER_LAUNCHER** —
* **CMAKE_MSVCIDE_RUN_PATH** –
* **CMAKE_NO_VERBOSE** –
* **CMAKE_OSX_ARCHITECTURES** –
* **DESTDIR** –
* **LDFLAGS** –
* **MACOSX_DEPLOYMENT_TARGET** –
* **\<PackageName\>_ROOT** –
* **VERBOSE** –

##### Для языков программирования

* **ASM\<DIALECT\>** –
* **ASM\<DIALECT\>FLAGS** –
* **CC** –
* **CFLAGS** –
* **CSFLAGS** –
* **CUDACXX** –
* **CUDAFLAGS** –
* **CUDAHOSTCXX** –
* **CXX** –
* **CXXFLAGS** –
* **FC** –
* **FFLAGS** –
* **RC** –
* **RCFLAGS** –
* **SWIFTC** –

##### CTest

* **CMAKE_CONFIG_TYPE** –
* **CTEST_INTERACTIVE_DEBUG_MODE** –
* **CTEST_OUTPUT_ON_FAILURE** –
* **CTEST_PARALLEL_LEVEL** –
* **CTEST_PROGRESS_OUTPUT** –
* **CTEST_USE_LAUNCHERS_DEFAULT** –
* **DASHBOARD_TEST_FROM_CTEST** –

#### Генераторы

* **Borland Makefiles** –
* **MSYS Makefiles** –
* **MinGW Makefiles** –
* **NMake Makefiles** –
* **NMake Makefiles JOM** –
* **Unix Makefiles** –
* **Watcom WMake** –
* **Ninja** –
* **Ninja Multi-Config** –
* **Visual Studio** –
  * Visual Studio 6
  * Visual Studio 7
  * Visual Studio 7 .NET 2003
  * Visual Studio 8 2005
  * Visual Studio 9 2008
  * Visual Studio 10 2010
  * Visual Studio 11 2012
  * Visual Studio 12 2013
  * Visual Studio 14 2015
  * Visual Studio 15 2017
  * Visual Studio 16 2019
* **Green Hills MULTI** –
* **Xcode** –
* **CodeBlocks** –
* **CodeLite** –
* **Eclipse CDT4** –
* **Kate** –
* **Sublime Text 2** –

#### Подключение внешних библиотек

```cmake
add_library(netutil STATIC IMPORTED)
set_property(TARGET netutil PROPERTY
            IMPORTED_LOCATION 
            Binary/game_client/libnetutil.a)
target_link_libraries(game netutil)
```

