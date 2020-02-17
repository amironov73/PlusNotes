### Настройка сборки

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

#### Visual Studio

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

Дополнительно можно указать необходимый [тулсет](../Toolsets.md)

```
> cmake -G "Visual Studio 14 2015 Win64" -T v140 ..
```

#### MinGW

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

#### Подключение внешних библиотек

```cmake
add_library(netutil STATIC IMPORTED)
set_property(TARGET netutil PROPERTY
            IMPORTED_LOCATION 
            Binary/game_client/libnetutil.a)
target_link_libraries(game netutil)
```

#### Добавление исходных файлов "скопом", а не по одному

```cmake
project(irbis)

FILE(GLOB HeaderFiles *.h)
FILE(GLOB CppFiles *.cpp)

set(SOURCES ${CppFiles} ${HeaderFiles})

add_library(irbis SHARED ${SOURCES})
```
