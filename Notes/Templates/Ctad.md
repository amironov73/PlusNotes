### CTAD

https://habr.com/ru/post/470265/

*Class Template Argument Deduction. Автоматический вывод типа параметра шаблона класса.* Это новая возможность из C++17. Раньше автоматически выводились только типы переменных (`auto`) и параметры шаблонов функций, из-за чего и возникли вспомогательные функции типа `std::make_pair`, `std::make_tuple` и т. п. Теперь они по большей части не нужны, т. к. компилятор способен автоматически вывести и параметры шаблонов классов:

```c++
std::pair p{1, 2.0}; // -> std::pair<int, double>
auto lck = std::lock_guard{mtx}; // -> std::lock_guard<std::mutex>
```

CTAD – новая возможность, ей еще развиваться и развиваться (С++20 уже обещает улучшения). Пока же ограничения таковы:

* Не поддерживается частичный вывод типов параметров

  ```c++
  std::pair<double> p{1, 2}; // ошибка
  std::tuple<> t{1, 2, 3};   // ошибка
  ```
  
* Не поддерживаются псевдонимы шаблонов

  ```c++
  template <class T, class U>
  using MyPair = std::pair<T, U>;
  MyPair p{1, 2}; // ошибка
  ```
  
* Не поддерживаются конструкторы, имеющиеся только в специализациях шаблона

  ```c++
  template <class T>
  struct Wrapper {};

  template <>
  struct Wrapper<int>
  {
    Wrapper(int) {};
  };
  Wrapper w{5}; // ошибка
  ```
  
* Не поддерживаются вложенные шаблоны

  ```c++
  template <class T>
  struct Foo
  {
    template <class U>
    struct Bar
    {
        Bar(T, U) {};
    };
  };
  Foo::Bar x{ 1, 2.0 };    // ошибка
  Foo<int>::Bar x{1, 2.0}; // OK
  ```
  
* Очевидно, CTAD не сработает, если тип параметра шаблона никак не связан с аргументами конструктора

  ```c++
  template <class T>
  struct Collection
  {
    Collection(std::size_t size) {};
  };
  Collection c{5}; // ошибка
  ```

В некоторых случаях помогут явные правила вывода, которые должны быть объявлены в том же блоке, что и шаблон класса.

Пример

```c++
template <class T>
struct Collection
{
    template <class It>
    Collection(It from, It to) {};
};
Collection c{v.begin(), v.end()}; // ошибка

template <class It>
auto Collection(It, It)->Collection<typename std::iterator_traits<It>::value_type>;
Collection c{v.begin(), v.end()}; // теперь OK
```
