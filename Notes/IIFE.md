### IIFE

https://habr.com/ru/post/470265/

*Immediately-Invoked Function Expression. Немедленно вызываемое функциональное выражение.* Вообще это идиома в JavaScript, откуда Джейсон Тёрнер (Jason Turner) ее и позаимствовал вместе с названием. По факту это просто создание и немедленный вызов лямбды:

```c++
const auto myVar = [&] {
    if (condition1())
    {
        return computeSomeComplexStuff();
    }
    return condition2() ? computeSonethingElse() : DEFAULT_VALUE;
} ();
```

Зачем это надо? Ну например, как в приведенном коде для того, чтобы инициализировать константу результатом нетривиального вычисления и не засорить при этом область видимости лишними переменными и функциями.
