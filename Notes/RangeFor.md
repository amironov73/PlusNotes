### range-based for loop

Цикл `for`, выполняемый над диапазоном. Появился в C++11. Заметно повышает читабельность кода.

Синтаксис:

**for ( range_declaration : range_expression) loop_statement**		

Пример:

```c++
vector<int> numbers;
for (auto number : numbers)
{
    std::cout << number << ", ";
}
```

Компилятор разворачивает примерно в следующую последовательность действий:

```c++
{
    auto &&rangeVar = range_expression;
    auto beginIter = std::begin (rangeVar); // или rangeVar.begin()
    auto endIter = std::end (rangeVar);     // или rangeVar.end()
    for ( ; beginIter != endIter; ++beginIter)
    {
        auto rangeItem = *beginIter;
        loop_statement;
    }
}
```

Как и в обычном цикле, допускается использование `break` и `end`.

В качестве `range_expression` можно использовать `initializer_list`:

```c++
for (auto x : { 1, 2, 3, 4 })
{
    std::cout << x << "\n";
}
```

Начиная с C++17, работает структурное связывание:

```c++
for (auto && [first, second] : mymap) {
    std::cout << first << ": " << second << "\n";
}
```

Начиная с C++20, допускается инициализация:

**for ( init-statement range_declaration : range_expression ) loop_statement**

например:

```c++
for (T thing = foo(); auto &x : thing.items()) 
{
    std::cout << x << "\n"; 
}
```

