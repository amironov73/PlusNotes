### Атрибут cleanup

Компиляторы GCC и Clang предоставляют замечательный атрибут `cleanup`, который позволяет значительно упростить работу с памятью (да и другими норовящими «утечь» ресурсами тоже). Следующий код демонстрирует использование этого атрибута:

```c
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    void do_cleanup (void **value)
    {
        free (*value);
        printf ("Freeing %p\n", *value);
    };

    __attribute__((cleanup (do_cleanup)))
    void* pointer = malloc (100);
 
    printf ("Allocated at %p\n", pointer);
 
    return 0;
}
```

Здесь заодно задействована вложенная функция — ещё одно замечательное расширение GCC и Clang.

С помощью `cleanup` и малой макро-механизации народ умудрился изобразить для C даже аналог smart pointer: https://habr.com/ru/post/503536.

```c
#include <stdio.h>
#include <csptr/smart_ptr.h>
#include <csptr/array.h>

void print_int (void *ptr, void *meta)
{
    (void) meta;
    // ptr points to the current element
    // meta points to the array metadata (global to the array), if any.
    printf ("%d\n", *(int*) ptr);
}

int main (void)
{
    // Destructors for array types are run on every element of the
    // array before destruction.
    smart int *ints = unique_ptr (int[5], {5, 4, 3, 2, 1}, print_int);
    // ints == {5, 4, 3, 2, 1}

    // Smart arrays are length-aware
    for (size_t i = 0; i < array_length (ints); ++i) {
        ints[i] = i + 1;
    }
    // ints == {1, 2, 3, 4, 5}
 
    return 0;
}
```

Согласитесь, для C довольно впечатляюще.

Этой возможностью воспользовались, например, в GLib: см. [g_autoptr](https://developer.gnome.org/glib/stable/glib-Miscellaneous-Macros.html).

Но есть и подводные грабли: необходимо остерегаться повторного входа в область видимости переменной (например, во вложенном блоке кода).

Visual C++ ничего подобного не поддерживает. :(

Разве что использовать `__try/__finally`:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    void* pointer = malloc (100);

    __try
    {
        printf ("Allocated at %p\n", pointer);
    }
    __finally
    {
        free (pointer);
        printf ("Freeing %p\n", pointer);
    }

    return 0;
}
```
