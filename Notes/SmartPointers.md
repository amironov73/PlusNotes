### Умные указатели

Заголовочный файл `<memory>`. Начиная с C++ 11.

#### unique_ptr

Указатель, владеющий объектом и не желающий делиться владением.

```c++
template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;
```

Специальная утилитная функция `make_unique` (начиная с C++ 14):

```c++
template< class T, class... Args >
unique_ptr<T> make_unique( Args&&... args ); // создаёт указатель на единичный объект

template< class T >
unique_ptr<T> make_unique( std::size_t size ); // массив объектов заданного размера.
```

Пример кода:

```c++
#include <iostream>
#include <memory>
#include <utility>

static int count = 0;

struct Destructible
{
    int value { 0 };
    Destructible() : value { ++count } {}
    ~Destructible() { std::cout << "destruct: " << value << std::endl; }
};

int main()
{
    auto u1 = std::make_unique<Destructible>();
    auto u2 = std::make_unique<Destructible>();
    std::swap (u1, u2);
    auto u3 = std::move (u2);
    std::cout << u3->value << std::endl;
    std::unique_ptr<Destructible> u4; // пустой

    return 0;
}

// 1
// destruct: 1
// destruct: 2
```

#### shared_ptr

Указатель, владеющий объектом и допускающий существование других владельцев.

```c++
template< class T > class shared_ptr;
```

Специальная утилитная функция `make_shared`:

```c++
template< class T, class... Args >
shared_ptr<T> make_shared( Args&&... args ); // начиная с C++ 11
```

#### weak_ptr

Слабая ссылка на `shared_ptr` (не увеличивающая счётчик).

```c++
template< class T > class weak_ptr;
```
