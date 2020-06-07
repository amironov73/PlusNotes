### Библиотека zlib

zlib — свободная кроссплатформенная библиотека для сжатия данных, созданная Жан-Лу Гайи и Марком Адлером. Является обобщением алгоритма сжатия данных DEFLATE, используемого в их компрессоре данных gzip. Первая публичная версия 0.9, выпущена 1 мая 1995 года для использования вместе с библиотекой libpng.

zlib применяется везде, начиная с ядра Linux, заканчивая World of Warcraft, поэтому расхваливать её нет смысла. Есть смысл идти на официальный сайт https://www.zlib.net, скачивать и изучать.

Первое, что мы замечаем в распакованных исходниках – файл `CMakeListst.txt`. Пара щелчков мышью – и мы получили файлы `zconf.h`, `zlibd.dll`, `zlibd.exp`, `zlibd.lib` и `zlibd.pdb` (по умолчанию под Windows собирается отладочная версия динамической библиотеки). Отлично! Теперь создаём новый проект в CLion и складываем эти файлы плюс `zlib.h` в папку `zlib` внутри этого проекта. Дополняем наш `CMakeLists.txt` следующим образом

```cmake
cmake_minimum_required(VERSION 2.8)
project(helloZlib)
 
set(CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR}/zlib)
link_directories(${PROJECT_SOURCE_DIR}/zlib)
link_libraries(zlibd.lib)
add_executable(helloZlib main.cpp)
```

Все готово! Можно начинать экспериментировать со сжатием/разжатием.

Пример простого сжатия/разжатия данных в оперативной памяти:

```c++
#include <iostream>
#include "zlib.h"
 
int main ()
{
    Bytef message[] = "Lorem ipsum dolor sit amet, consectetur adipiscing "
                     "elit, sed do eiusmod tempor incididunt ut labore et "
                     "dolore magna aliqua. Elit pellentesque habitant morbi "
                     /* ещё много строк */;
 
    Bytef buf1 [1024], buf2 [1024];
    uLongf len1 = sizeof (buf1), len2 = sizeof (buf2);
    std::cout << "Source length=" << sizeof (message) << std::endl;
 
    uLongf need = compressBound (sizeof (message));
    std::cout << "Needed=" << need << std::endl;
 
    memset (buf1, 0, sizeof (buf1));
    int rc = compress2 (buf1, &len1, message, sizeof (message),
        Z_BEST_COMPRESSION);
    if (rc != Z_OK) {
        std::cerr << "Compress error=" << rc << std::endl;
        return 1;
    }
    std::cout << "Compressed length=" << len1 << std::endl;
 
    memset (buf2, 0, sizeof (buf2));
    rc = uncompress (buf2, &len2, buf1, len1);
    if (rc != Z_OK) {
        std::cerr << "Uncompress error=" << rc << std::endl;
        return 2;
    }
    std::cout << "Uncompressed length=" << len2 << std::endl;
 
    return 0;
}
```

Пример потокового сжатия:

```c++
#include <iostream>
#include "zlib.h"
 
int main ()
{
    Bytef message1[] = "Lorem ipsum dolor sit amet, consectetur adipiscing "
                     "elit, sed do eiusmod tempor incididunt ut labore et "
                     /* ещё много строк */;
 
    Bytef message2[] = "Odio eu feugiat pretium nibh ipsum consequat. "
                     "Amet consectetur adipiscing elit pellentesque habitant. "
                     /* ещё много строк */;
 
    z_stream stream { 0 };
    memset (&stream, 0, sizeof (stream));
    if (deflateInit (&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        std::cerr << "Initialization failed" << std::endl;
        return 1;
    }
 
    Bytef buf1 [1024];
 
    stream.next_in = message1;
    stream.avail_in = sizeof (message1);
    stream.next_out = buf1;
    stream.avail_out = sizeof (buf1);
 
    if (deflate (&stream, Z_SYNC_FLUSH) != Z_OK) {
        std::cerr << "deflate failed" << std::endl;
        return 2;
    }
 
    auto portionSize = sizeof (buf1) - stream.avail_out;
    std::cout << "First portion=" << portionSize << std::endl;
 
    // Вторая порция данных – завершающая.
    stream.next_in = message2;
    stream.avail_in = sizeof (message2);
    stream.next_out = buf1;
    stream.avail_out = sizeof (buf1);
 
    if (deflate (&stream, Z_FINISH) != Z_STREAM_END) {
        std::cerr << "deflate failed" << std::endl;
        return 3;
    }
 
    portionSize = sizeof (buf1) - stream.avail_out;
    std::cout << "Second portion=" << portionSize << std::endl;;
 
    if (deflateEnd (&stream) != Z_OK) {
        std::cerr << "Cleanup failed" << std::endl;
        return 4;
    }
 
    return 0;
}
```

Файловый ввод-вывод:

```c++
#include <iostream>
#include "zlib.h"
 
int main ()
{
    Bytef content[] = "Lorem ipsum dolor sit amet, consectetur adipiscing"
                      " elit, sed do eiusmod tempor incididunt ut labore "
                      /* ещё много строк */;
 
    std::cout << "Content length=" << sizeof (content) << std::endl;
 
    gzFile output = gzopen("compressed.data", "wb");
    if (!output) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
 
    if (!gzwrite (output, content, sizeof (content))) {
        std::cerr << "Error writing file" << std::endl;
        return 2;
    }
 
    if (gzclose (output) != Z_OK) {
        std::cerr << "Error closing file" << std::endl;
        return 3;
    }
 
    std::cout << "Done writing file" << std::endl;
 
    gzFile input = gzopen ("compressed.data", "rb");
    if (!input) {
        std::cerr << "Error opening file" << std::endl;
        return 4;
    }
 
    Bytef buffer [1024];
    if (gzread (input, buffer, sizeof(buffer)) != sizeof(content)) {
        std::cerr << "Error reading file" << std::endl;
        return 5;
    }
 
    if (gzclose (input) != Z_OK) {
        std::cerr << "Error closing file" << std::endl;
        return 6;
    }
 
    std::cout << "Done reading file" << std::endl;
 
    return 0;
}
```

Как подсчитать CRC32 с помощью ZLIB:

```c++
uLong crc = crc32 (0L, Z_NULL, 0);
while (read_buffer (buffer, length) != EOF) {
    crc = crc32 (crc, buffer, length);
}
 
if (crc != original_crc) {
    error();
}
```
