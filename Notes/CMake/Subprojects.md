### Подпроекты

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
