### static_assert

Аналог давно известного `assert`, срабатывающий во время компиляции:

```c++
template <class T, int N>
class Matrix
{
    static_assert (N > 3, "Size is too big");

    T items[N][N];
};
```

В примере выше, если задать

```c++
Matrix<double, 4> matrix;
```

компилятор остановится с диагностикой

```
error C2338: Size is too big
```

Удобно использовать `static_assert` совместно с `<type_traits>`.
