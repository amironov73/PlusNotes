### C++11

https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP11.md

https://habr.com/ru/post/182920/

#### auto

Ключевое слово `auto` позволяет не указывать тип переменной, компилятор выведет его самостоятельно:

```c++
auto count = 123; // int
auto hello = "Hello!"; // const char*
auto something = new SomeThing; // SomeThing*
```

В заголовке функции `auto` означает "тип возвращаемого значения указан после параметров":

```c++
template <typename T1, typename T2>
auto sum (T1 a, T2 b) -> decltype (a + b)
{
    return a + b;
}
```

#### nullptr

`nullptr` должен применяться везде вместо `NULL` и `0`. У него собственный тип `std::nullptr_t`, которым можно специализировать шаблоны. Существуют неявные преобразования nullptr к нулевому указателю любого типа и к bool (как false), но преобразования к целочисленных типам нет.

#### range-for

[См.](RangeFor.md)

#### override и final

```c++
class A
{
public:
    virtual void SomeFunction();
};

class B: public A
{
public:
    void SomeFunction() override; // virtual можно опустить
};

class C: public C
{
public:
    void SomeFunction() override final;
};
```

#### enum class

```c++
enum class TrafficLight
{
    Red,
    Yellow,
    Green
};
```

Обратиться к значениям можно только `TrafficLight::Red` и т. д. Неявные преобразования из/в целое запрещены. Для использования флагов нужно определять оператор `|`:

```c++
TrafficLight operator | (TrafficLight left, TrafficLight right);
```

#### умные указатели

[См.](STL/SmartPointers.md)

#### лямбда-функции

[См.](Lambda.md)

#### std::begin и std::end

С целью унификации определены две шаблонные функции: `std::begin` и `std::end`. Для контейнеров они просто вызывают члены `begin` и `end` . Однако добавлены перегрузки и для массивов в стиле C.

#### static_assert

[См.](StaticAssert.md)

#### семантика перемещения

[См.](Move.md)
