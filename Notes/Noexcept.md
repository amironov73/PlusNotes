### Спецификатор noexcept

Спецификатор `noexcept` указывается для функций (в т. ч. функций-членов класса) в одной из трёх форм:

* `noexcept` -- означает то же, что `noexcept(true)`;
* `noexcept(bool)` -- статически задаёт спецификацию исключений;
* `noexcept(expression)` -- динамически задаёт спецификацию в зависимости от каких-либо условий.

Примеры:

```c++
int func1() noexcept
{
    return 42;    
}

int func2(int a, int b) noexcept(true)
{
    return a + b;    
}

int func3(int a) noexcept(boolean_expression_known_at_compile_time)
{
    do_something(a);
}
```