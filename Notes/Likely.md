### C++20 likely-unlikely

https://en.cppreference.com/w/cpp/language/attributes/likely

В C++20 появились атрибуты `[[likely]]` и `[[unlikely]]`. Их назначение просто: пометить те ветки исполнения программы, которые программист считает наиболее и наименее вероятными соответственно. Это подсказка для оптимизатора (заметим, что оптимизатор не обязан строго следовать нашим подсказкам!).

```c++
#include <iostream>
#include <stdexcept>
 
void saySomething (const char *text)
{
    if (text == nullptr) [[unlikely]] {
        throw std::invalid_argument("text is null");
    }
    std::cout << "Something: " << text << std::endl;
}
 
int compute (int x, int y)
{
    if (x < y) [[likely]] {
        return (x - y) * 2;
    }
    else {
        return (y - x) / 2;
    }
}
 
int choose(int n)
{
    switch (n) {
        case 0: return 111;
        case 1: return 222;
        [[unlikely]] default: return 0;
    }
}
 
int main ()
{
    saySomething("Hello");
    std::cout << compute (5, 1) << std::endl;
    std::cout << choose (1) << std::endl;
    return 0;
}
```

Короче, появился ещё один способ изощрённо выстрелить себе в ногу. 🙂
