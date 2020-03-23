### Итераторы

Итераторы в C++ - это обобщение понятия указатель:

* Итератор можно разыменовать с помощью оператора `*` звездочка (и получить доступ к некоторому объекту, если, конечно, итератор ссылается на какой-либо объект).

* Итератор можно подвинуть на одну позицию с помощью оператора `++`, после чего итератор будет ссылаться на новый объект, либо станет невалидным.

* Итератор можно сравнить с другим итератором с помощью оператора `!=`, чтобы убедиться, что конец еще не достигнут.

Как правило, с итератором можно проделывать и другие действия (например, двигать его с помощью оператора `--` или сравнивать с помощью оператора `==`), но выше перечислены основные требования.

Как отлично видно, простой указатель `T*` на 100% удовлетворяет всем вышеперечисленным требованиям.

### Свой итератор к своему контейнеру

```c++
#include <iostream>
#include <iterator>
#include <string>
 
// предварительное объявление
template <class T> class Few;
template <class T> class Ite;
 
// контейнер на три элемента
template <class T>
class Few
{
    friend class Ite<T>;
public:
    typedef Ite<T> iterator;
 
    Few (T &&arg1, T &&arg2, T &&arg3)
        : first (arg1), second (arg2), third (arg3) {}
    iterator begin() { return Ite<T> (*this, 0); }
    iterator end() { return Ite<T> (*this, 3); }
 
private:
    T first, second, third;
};
 
// итератор по контейнеру
template <class T>
class Ite : public std::iterator<std::input_iterator_tag, T>
{
    friend class Few<T>;
public:
    Ite(const Ite<T> &other)
        : container (other.container),
        position (other.position) {}
 
    bool operator != (const Ite<T> &other)
        { return position != other.position; }
    Ite<T>& operator ++()
        { ++position; return *this; }
    Ite<T>& operator --()
        { --position; return *this; }
 
    T& operator *() {
        switch (position) {
            case 0: return container.first;
            case 1: return container.second;
            case 2: return container.third;
            default: std::terminate();
        }
    }
 
private:
    Ite(Few<T> &arg1, std::ptrdiff_t arg2)
            : container (arg1), position (arg2) {}
    Few<T> &container;
    std::ptrdiff_t position;
};
 
int main()
{
    Few<std::string> few ("first", "second", "third");
    for (const auto &item : few) {
        std::cout << item << std::endl;
    }
 
    std::cout << "============" << std::endl;
 
    auto iter1 = std::end (few);
    const auto iter2 = std::begin (few);
    while (iter1 != iter2) {
        --iter1;
        std::cout << *iter1 << std::endl;
    }
 
    return 0;
}
```
