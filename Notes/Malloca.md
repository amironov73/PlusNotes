### Функция _malloca

Функция [`_malloca`](https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/reference/malloca?view=vs-2019) в Visual C++ runtime является гибридом `alloca` и `malloc` (и это отражено в её названии). Вот её прототип:

```c
#include <malloc.h>
 
void* _malloca (size_t size);
```

Если размер запрошенного блока не превышает `_ALLOCA_S_THRESHOLD` (на данный момент 1024), она выделяет память на стеке (совсем как `alloca`), иначе – в куче (аналогично `malloc`). Парная к ней функция освобождения памяти называется `_freea`.

```c
#include <stdio.h>
#include <malloc.h>
 
int main()
{
    void *ptr;
 
    printf ("Treshold is %d\n",  _ALLOCA_S_THRESHOLD);
 
    ptr = _malloca (100);
    printf ("Allocated at %p\n", ptr);
    _freea (ptr);
 
    return 0;
}
```

Вот как реализована `_malloca`:

```c
#define _malloca(size)                                                             \
__pragma(warning(suppress: 6255 6386))                                             \
(_MallocaComputeSize(size) != 0                                                    \
    ? (((_MallocaComputeSize(size) <= _ALLOCA_S_THRESHOLD)                         \
        ? _MarkAllocaS(_alloca(_MallocaComputeSize(size)), _ALLOCA_S_STACK_MARKER) \
        : _MarkAllocaS(malloc(_MallocaComputeSize(size)), _ALLOCA_S_HEAP_MARKER))) \
    : NULL)
```
