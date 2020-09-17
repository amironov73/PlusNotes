### До и после main

Бывает, что у нас есть сишный код, и нам необходимо выполнить некоторую инициализацию до `main`. Эта ситуация становится особенно щекотливой, когда наш код расположен в библиотеке.

В GCC и Clang эта проблема решается просто:

```c
#include <stdio.h>
 
static void beforeMain (void) __attribute__((constructor));
static void afterMain  (void) __attribute__((destructor));
 
static void beforeMain (void)
{
    printf ("\nbefore main\n");
}
 
static void afterMain (void)
{
    printf ("\nafter main\n");
}
 
int main()
{
    printf ("Hello, World!\n");
    printf ("Hello, World Again!\n");
 
    return 0;
}
```

Писать надо именно так: отдельно объявление функции с атрибутом `constructor`, отдельно – определение с телом. Не знаю, почему так, наверное, есть какие-то резоны.

Для Visual C++ заклинания выглядят заметно навороченнее. Чтобы запуститься перед `main`, необходимо в сегменте данных `.CRT$XCU` [разместить указатель на функцию](https://docs.microsoft.com/en-us/cpp/c-runtime-library/crt-initialization?view=vs-2019) с сигнатурой `int func (void)`. «Посмертные» же функции [регистрируются вызовом](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atexit?view=vs-2019) `atexit`.

```c
#include <stdio.h>
#include <stdlib.h>
 
static int beforeMain (void)
{
    printf ("\nbefore main\n");
    return 0;
}
 
#ifdef _WIN64
 
#pragma section(".CRT$XCU",read)
__declspec(allocate(".CRT$XCU")) static int (*p) (void) = beforeMain;
 
#else
 
#pragma data_seg(".CRT$XCU")
static int (*p) (void) = beforeMain;
 
#endif
 
#pragma data_seg()
 
static void afterMain (void)
{
    printf ("\nafter main\n");
}
 
int main()
{
    atexit (afterMain);
    printf ("Size of pointer=%d\n", (int) sizeof (void*));
    printf ("Hello, World!\n");
    printf ("Hello, World Again!\n");
 
    return 0;
}
```

Я бы не сказал, что это запредельно сложно, но у GCC сделано по-человечески, а MS как обычно через задницу.
