### Подключение Boost в CMake

Традиционно в CMake принято подключать Boost с помощью штатной функции find_package. Полный синтаксис:

```cmake
find_package(Boost
  [version] [EXACT]      # Минимальна или ТОЧНАЯ версия, например, 1.67.0
  [REQUIRED]             # Выдавать ошибку, если не Boost не найден
  [COMPONENTS <libs>...] # Конкретные компоменты (канонические имена)
                         # например, "date_time" для "libboost_date_time"
  [OPTIONAL_COMPONENTS <libs>...]
                         # Опциональные компоненты (канонические имена)
  )                      # например, "date_time" для "libboost_date_time"
```

Пакет `FindBoost.cmake`, кроме прочего, ориантируется на следующие переменные окружения:

* **BOOST_ROOT** или **BOOSTROOT** - директория с установленным Boost;
* **BOOST_INCLUDEDIR** - предпочитаемая директория с заголовочными файлами;
* **BOOST_LIBRARYDIR** - предпочитаемая директория с библиотеками;
* **Boost_NO_SYSTEM_PATHS** - запрет поиска Boost по системным путям;
* **Boost_ADDITIONAL_VERSIONS** - перечень дополнительных версий Boost, неизвестных пакету.

По результатам создаются следующие переменные:

* **Boost_FOUND** - True если удалось найти;
* **Boost_INCLUDE_DIRS** - директория с заголовочными файлами;
* **Boost_LIBRARY_DIRS** - директория с библиотеками;
* **Boost_LIBRARIES** - перечень библиотек для линковки.

Начиная с CMake 3.12 добавилась возня с полиси `CMP0074`. Если она равна `NEW`, то `find_package` использует переменную окружения `BOOST_ROOT`, если равна `OLD`, игнорирует её. (В скобках замечу, что эта полиси распространяется на все пакеты, подключаемые с помощью `find_package`, а не только на Boost.)

Пример применения:

```cmake
cmake_minimum_required(VERSION 3.12)
project(learnBoost)

cmake_policy(SET CMP0074 NEW)
find_package(Boost 1.72.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(learnBoost main.cpp)
```
