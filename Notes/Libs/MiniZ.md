### Библиотека miniz

Несмотря на схожесть названий, библиотека `miniz` представляет собой в некотором смысле противоположность `minizip`. Она представляет собой однофайловую библиотеку, которую можно подключить к своему проекту простым копированием, и делает ровно одну вещь — сжимает/разжимает данные по алгоритму deflate/inflate из `zlib`. Т. е. вместо универсального комбайна мы получаем ровно один инструмент, простой как молоток и столь же эффективный. 🙂

Официальный сайт: https://code.google.com/archive/p/miniz (оригинальный проект), GitHub: https://github.com/richgel999/miniz (перенесён на GitHub).

Пример использования (я скопировал `miniz.c` в папку программы рядом с `main.cpp`):

```c++
#include <iostream>
#include <cstring>
#include "miniz.c"
 
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
