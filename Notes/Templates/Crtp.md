### Curiously Recurring Template Pattern

Wiki: https://ru.wikipedia.org/wiki/Curiously_recurring_template_pattern, https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern.

https://habr.com/ru/post/470265/

*Curiously Recurring Template Pattern (CRTP)* идиома языка C++, название которой можно примерно перевести как Странно рекурсивный шаблон или Странно повторяющийся шаблон, часто просто Рекурсивный Шаблон, состоящая в том, что некоторый класс X наследуется от шаблона класса, использующего X как шаблонный параметр.

Используется и в Java — например, любой `enum X` является наследником от `Enum<X>`.

```c++
#include <iostream>
 
struct Data {};
 
template <class T>
class Socket
{
public:
    void send (const Data &data)
    {
        asDerived()->send_implementation (data);
    }
 
    void receive(Data &data)
    {
        asDerived()->lreceive_implementation (data);
    }    
 
private:
    T* asDerived() { return static_cast<T*> (this); }
};
 
class TcpSocket: public Socket<TcpSocket>
{
public:
    void send_implementation (const Data &data)
    {
        std::cout << "SEND" << std::endl;
    }
 
    void receive_implementation (Data &data)
    {
        std::cout << "RECEIVE" << std::endl;
    }
};
 
int main ()
{
    Data data;
    TcpSocket socket;
    socket.send (data);
    socket.receive (data);
    return 0;
}
```

CRTP — яркий пример статического полиморфизма. Базовый класс предоставляет интерфейс, классы-наследники — реализацию. Но в отличие от обычного полиморфизма здесь нет накладных расходов на создание и использование таблицы виртуальных функций.

Пример

```c++
template <typename T>
struct Base
{
    void action() const { static_cast<T*>(this)->actionImpl(); }
};

struct Derived : Base<Derived>
{
    void actionImpl() const { ... }
};

template <class Arg>
void staticPolymorphicHandler(const Arg& arg)
{
    arg.action();
}
```

При правильном использовании `T` всегда является потомком `Base`, поэтому для приведения достаточно `static_cast`. Да, в данном случае базовый класс знает интерфейс потомка.

Еще одной частой областью использования CRTP является расширение (или сужение) функциональности наследных классов (то, что в некоторых языках называется mixin). Пожалуй самые известные примеры:

* `struct Derived : singleton<Derived> { … }`
* `struct Derived : private boost::noncopyable<Derived> { … }`
* `struct Derived : std::enable_shared_from_this<Derived> { … }`
* `struct Derived : counter<Derived> { … }` — подсчет числа созданных и/или существующих объектов
    ``

Недостатки, или, скорее, требующие внимания моменты:

* Нет общего базового класса, не получится создать коллекцию разных потомков и обращаться к ним через указатель на базовый тип. Но если хочется, можно унаследовать Base от обычного полиморфного типа.
* Есть дополнительная возможность отстрелить себе ногу по невнимательности:

  Пример
  ```c++
  template <typename T>
  struct Base {};
      
  struct Derived1 : Base<Derived1> {};
  struct Derived2 : Base<Derived1> {};
  ```

  Но можно добавить защиту:

  ```c++
  private:
    Base() = default;
    friend T;
  ```
    
* Т.к. все методы невиртуальные, то методы потомка скрывают методы базового класса с теми же именами. Поэтому лучше называть их по-другому.
* И вообще, у потомков есть публичные методы, которые нигде, кроме базового класса, использоваться не должны. Это нехорошо, но исправляется через дополнительный уровень абстракции (см. FTSE).
