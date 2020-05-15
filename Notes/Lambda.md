### Лямбда-функция

https://en.cppreference.com/w/cpp/language/lambda

Лямбда - безымянный объект-функция, способный захватывать переменные в контекст. Появилась в C++11.

Полный синтаксис:

**\[ captures \] ( params ) mutable noexcept -> ret { body }**

Здесь:

* **captures** - захватываемые переменные:

    * \[&\] - захват всех упоминаемых переменных по ссылке;
    * \[=\] - захват всех упоминаемых переменных по значению;
    * \[i, j, k\] - захват перечисленных переменных по значению;
    * \[&i, &j, &k\] - захват перечисленных переменных по ссылке;
    * \[this\] - `this` тоже можно захватывать;
 
    Захватывать можно только переменные методов/функций либо нестатические члены класса (с помощью `this`). Глобальные переменные или статические члены классов захватывать нельзя.
    
    В блоке caputres, начиная с C++14, можно вводить собственные переменные. Более того, их можно сохранять между вызовами лямбды:
    
    ```c++
    auto func = [y = 0] () mutable { return ++y; };

    std::cout << func() << std::endl; // напечатает 1
    std::cout << func() << std::endl; // напечатает 2
    ```
    
    Если лямбда входит в variadic-шаблон, она может захватить весь type pack: `[args...]`.
 
    Примеры блоков captures:
 
    ```
    [&total, factor]
    [factor, &total]
    [&, factor]
    [factor, &]
    [=, &total]
    [&total, =]
    ```
 
* **params** - список параметров лямбды. Объявляется как в обычной функции:
 
    ```c++
    auto func = [] (int first, int second) { return x + y; };
    ```
 
    Пустой перечень можно опустить. Безымянные параметры не допускаются. 
    
    Начиная с C++14, можно писать `(auto x)` - таким образом задаются шаблонные лямбды:
    
    ```c++
    auto y = [] (auto first, auto second) { return first + second; };    
    ```
  
    Вышеприведенная лямбда превращается компилятором в примерно следующее:
    
    ```c++
    struct Lambda1
    {
        template <typename FirstType, typename SecondType>
        auto operator () (FirstType first, SecondType second) -> decltype (first + second)
        {
            return first + second;
        } 
    };
    ```
  
* **mutable** - указывает, что лямбда должна сохранять свое состояние между вызовами. При использовании `mutable` список параметров опускать нельзя.

* **noexcept** - спецификация `noexcept`, такая же, как у обычных функций/методов. Также можно писать `throw(type)` и т. п.  

* **ret** - возвращаемый тип. Можно опустить, если компилятор в состоянии самостоятельно вывести тип. Для этого нужно, чтобы: 1) нет `return` вовсе, 2) есть единственный `return`, либо 2) несколько `return`, типы выражений для всех совпадают.

* **body** - обычное тело функции/метода. Можно даже употреблять лямбды внутри лямбды.

Начиная с C++17 появились constexpr-лямбды:

```c++
int y = 32;
auto answer = [y]() constexpr
{
    int x = 10;
    return y + x;
};
```

Более того, лямбда считается constexpr автоматически (т. е. без явного указания), если её тело соответствует требованиям к constexpr.

#### Лямбда с деструктором

[Увидел у Jason Turner](https://www.youtube.com/watch?v=9L9uSHrJA08). Не знаю пока, есть ли в этом практический смысл, но выглядит просто ошеломляюще. C++17:

```c++
#include <iostream>
 
int main ()
{
    auto lambda1 =
        [
            lambda2 = []
            {
                struct S
                {
                    int value = 123;
                    S() { std::cout << "Created\n"; }
                    S(const S&) { std::cout << "Copied\n"; }
                    S(S&&) noexcept { std::cout << "Moved\n"; }
                    ~S() { std::cout << "Destoryed\n"; }
                };
                return S {};
            } ()
        ]
    {
        return lambda2;
    };
 
    auto lambda3 = lambda1;
    return lambda3().value;
}
```

Выводит:

```
Created
Moved
Destoryed
Copied
Copied
Destoryed
Destoryed
Destoryed
```
