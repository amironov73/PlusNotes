### Библиотека Fast C++ CSV parser

GitHub: https://github.com/ben-strasser/fast-cpp-csv-parser.

Небольшая header-only библиотека для C++11, позволяющая разбирать CSV-файлы. Поддерживает UTF-8.

Пример файла, подлежащего разбору: taxes.csv

```
"Index", "Item",                            "Cost", "Tax", "Total"
     1,  "Fruit of the Loom Girl's Socks",    7.97,  0.60,    8.57
     2,  "Rawlings Little League Baseball",   2.97,  0.22,    3.19
     3,  "Secret Antiperspirant",             1.29,  0.10,    1.39
     4,  "Deadpool DVD",                     14.96,  1.12,   16.08
     5,  "Maxwell House Coffee 28 oz",        7.28,  0.55,    7.83
     6,  "Banana Boat Sunscreen, 8 oz",       6.68,  0.50,    7.18
     7,  "Wrench Set, 18 pieces",            10.00,  0.75,   10.75
     8,  "M and M, 42 oz",                    8.98,  0.67,    9.65
     9,  "Bertoli Alfredo Sauce",             2.12,  0.16,    2.28
    10,  "Large Paperclips, 10 boxes",        6.19,  0.46,    6.65
```

Пример считывания этого файла:

```c++
#include <iostream>
#define CSV_IO_NO_THREAD
#include "csv.h"
 
using CsvReader = io::CSVReader < 5,
    io::trim_chars <' ', '\t'>,
    io::double_quote_escape <',', '"'>
    >;
 
int main ()
{
    // Создаём ридер
    CsvReader in ("taxes.csv");
    in.read_header (io::ignore_extra_column,
        "Index", "Item", "Cost", "Tax", "Total");
 
    // Переменные, в которые будут считываться данные
    int index;
    std::string item;
    double cost, tax, total;
 
    // Цикл чтения
    while (in.read_row (index, item, cost, tax, total)) {
        std::cout << index << " " << item << " " < total << std::endl;
    }
 
    return 0;
}
```

Обратите внимание на #define CSV_IO_NO_THREAD. Так мы указываем, что необходимости в многопоточной обработке нет. Если многопоточность нужна, то необходимо убрать этот макрос и добавить -pthread в командную строку GCC/Clang.