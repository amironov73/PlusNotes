### Версия

Определены три переменные:

* CMAKE_MAJOR_VERSION, мажорная версия, цифра 2 в "2.3.4"
* CMAKE_MINOR_VERSION, минорная версия, цифра 3 в "2.3.4"
* CMAKE_PATCH_VERSION, патч, цифра 4 в "2.3.4"

Проверка версии:

```cmake
if(${CMAKE_VERSION} VERSION_LESS "3.8.0") 
    message("Лучше используйте CMake версии 3.8.0 или выше")
endif()
```
