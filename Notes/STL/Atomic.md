### std::atomic

Шаблоны для реализации атомарных операций. Атомарные объекты могут быть безопасно использоваться из нескольких потоков. Эти объекты сами разруливают многопоточный доступ.

Предусмотрены алиасы:

```c++
std::atomic_bool  == std::atomic<bool>
std::atomic_char  == std::atomic<char>
std::atomic_int   == std::atomic<int>
// и т. д.
```

Пример:

```c++
#include <iostream>
#include <atomic>
#include <thread>

std::atomic_int someValue (0);

void printer ()
{
    while (true) {
        int localCopy = someValue.load (std::memory_order_relaxed);
        if (localCopy == 10) {
            break;
        }
        std::cout << localCopy << std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds (100));
    }
}

void incrementer ()
{
    for (int i = 1; i < 11; ++i) {
        someValue.store (i, std::memory_order_relaxed);
        std::this_thread::sleep_for (std::chrono::milliseconds (150));
    }
}

int main ()
{
    std::thread first (printer);
    std::thread second (incrementer);
    first.join ();
    second.join ();

    return 0;
}
```
