### Шаблоны

В настоящее время шаблоны определяются так:

```
template < parameter-list > requires-clause (опционально, начиная с C++20) declaration
export template < parameter-list > declaration (до C++11)
template < parameter-list > concept concept-name = constraint-expression ; (начиная с C++20)
```

Допускается произвольное количество объявлений шаблона наряду с его определением:

```c++
#include <iostream>

template<class T> void print (const T& value);
template<class U> void print (const U& value); // излишне, но допустимо
template<class V> void print (const V& value); // излишне, но допустимо

template<class T>
void print(const T& value)
{
    std::cout << value << std::endl;
}

int main()
{
    print (std::string("Hello, world!"));
    return 0;
}
```
