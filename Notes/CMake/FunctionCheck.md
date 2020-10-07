### Проверка функций

Сначала о том, как проверить наличие заголовочных файлов.

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.1)
project(somecheck C)
 
INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES (malloc.h HAVE_MALLOC_H)
CHECK_INCLUDE_FILES (nosuchfile.h HAVE_NOSUCHFILE_H)
 
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)
 
include_directories(${CMAKE_CURRENT_BINARY_DIR})
 
set(CMAKE_C_STANDARD 90)
 
add_executable(somecheck main.c)
```

`config.h.in`:

```c
#cmakedefine HAVE_MALLOC_H
#cmakedefine HAVE_NOSUCHFILE_H
```

В результате получаем следующий `config.h`:

```c
#define HAVE_MALLOC_H
/* #undef HAVE_NOSUCHFILE_H */
```

Согласитесь, просто и понятно.

Теперь о том, как обнаруживать функции. Несмотря на то, что напрашивается `CheckFunctionExists`, лучше использовать более универсальный модуль `CheckSymbolExists`. `CMakeLists.txt`:

```cmake
INCLUDE(CheckSymbolExists)
CHECK_SYMBOL_EXISTS(alloca "malloc.h" HAVE_ALLOCA)
CHECK_SYMBOL_EXISTS(SEEK_SET "stdio.h" HAVE_SEEK_SET)
```

`config.h.in`:

```c
#cmakedefine HAVE_ALLOCA
#cmakedefine HAVE_SEEK_SET
```

В итоге получаем:

```c
#define HAVE_ALLOCA
#define HAVE_SEEK_SET
```

Обратите внимание: `SEEK_SET` – не функция, а `#define`, но он всё равно успешно обнаруживается CMake.

Есть ли в заголовочных файлах прототип нужной функции: `CMakeLists.txt`:

```cmake
INCLUDE(CheckPrototypeExists)
CHECK_PROTOTYPE_EXISTS(mkstemps "stdlib.h;unistd.h" HAVE_MKSTEMPS_PROTO)
```

Есть ли нужная библиотека:

```cmake
INCLUDE (CheckLibraryExists)
# CHECK_LIBRARY_EXISTS(library function location variable)
CHECK_LIBRARY_EXISTS(volmgt volmgt_running "" HAVE_VOLMGT)
```

Как определить размер типа: `CMakeLists.txt`:

```cmake
INCLUDE(CheckTypeSize)
SET(CMAKE_EXTRA_INCLUDE_FILES stdlib.h)
CHECK_TYPE_SIZE(size_t SIZEOF_SIZE_T)
SET(CMAKE_EXTRA_INCLUDE_FILES)
```

`config.h.in`:

```c
#cmakedefine SIZEOF_SIZE_T ${SIZEOF_SIZE_T}
```

В итоге получаем:

```c
#define SIZEOF_SIZE_T 8
```

Как определить компилятор и систему: `config.h.in`:

```c
#cmakedefine COMPILER ${CMAKE_C_COMPILER_ID}
#cmakedefine SYSTEM ${CMAKE_SYSTEM_NAME}
```

В итоге получаем:

```c
#define COMPILER MSVC
#define SYSTEM Windows
```

или

```c
#define COMPILER GNU
#define SYSTEM Linux
```

Идентификаторы компиляторов: AppleClang, ARMCC, ARMClang, Clang, Embarcadero, Borland, GNU, IAR, Intel, MSVC, NVIDIA, OpenWatcom, SDCC, TinyCC. Идентификаторы систем: Windows, Darwin, Linux, Android, FreeBSD, MSYS, CYGWIN.

Хорошие фичи, надо пользоваться! 🙂
