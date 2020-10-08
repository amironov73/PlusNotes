### Функция aligned_alloc

Обычная функция `malloc`, как гласит стандарт, возвращает указатель, выравненный достаточно, чтобы по указанному адресу можно было хранить любой объект. На практике это означает «зависит от системы». GCC гарантирует, что в 32-битной системе указатель выравнен на границе 8 байт, в 64-битной на границе 16 байт:

> The address of a block returned by malloc or realloc in the GNU system is always a multiple of eight (or sixteen on 64-bit systems).

Это здорово, но не всегда достаточно. Некоторые типы данных, например, AVX, требуют выравнивания на 32-байтную границу. Начиная с C11, функция [aligned_alloc](https://en.cppreference.com/w/c/memory/aligned_alloc) предлагает нам блоки памяти, адреса которых выравнены на указанную нами величину. Вот её прототип:

```c
void* aligned_alloc (size_t alignment, size_t size);
```

Освобождать память предлагается простым вызовом `free`, что радует. У плюсовиков [аналог этой функции](https://en.cppreference.com/w/cpp/memory/c/aligned_alloc) появился в C++17:

```c++
void* aligned_alloc (std::size_t alignment, std::size_t size);
```

Использовать функцию легко и просто (надо только не забыть включить C11 в командной строке gcc):

```c
#include <stdlib.h>
#include <stdio.h>

int main()
{
    void *ptr = aligned_alloc (32, 32);
    printf ("Allocated at %p\n", ptr);
    free (ptr);

    return 0;
}
```

Вот как [можно реализовать эту функцию](https://embeddedartistry.com/blog/2017/02/22/generating-aligned-memory/) самому:

```c
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

typedef uint16_t offset_t;
#define PTR_OFFSET_SZ sizeof (offset_t)

#ifndef align_up
#define align_up(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))
#endif

void* my_aligned_alloc (size_t alignment, size_t size)
{
    void *result = NULL;

    /* We want it to be a power of two since
       align_up operates on powers of two */
    assert ((alignment & (alignment - 1)) == 0);
 
    if (alignment && size)
    {
        /*
         * We know we have to fit an offset value
         * We also allocate extra bytes to ensure we
         * can meet the alignment
         */
        uint32_t headerSize = PTR_OFFSET_SZ + (alignment - 1);
        void *p = malloc (size + headerSize);
 
        if (p)
        {
            /*
             * Add the offset size to malloc's pointer
             * (we will always store that)
             * Then align the resulting value to the
             * target alignment
             */
            result = (void*) align_up (((uintptr_t) p + PTR_OFFSET_SZ), alignment);
 
            /* Calculate the offset and store it
               behind our aligned pointer */
            *((offset_t*) result - 1) =
                    (offset_t) ((uintptr_t) result - (uintptr_t) p);
 
        } /* else NULL, could not malloc */
    } /* else NULL, invalid arguments */
 
    return result;
}

void my_aligned_free (void *ptr)
{
    assert (ptr);

    /*
    * Walk backwards from the passed-in pointer
    * to get the pointer offset. We convert to an offset_t
    * pointer and rely on pointer math to get the data
    */
    offset_t offset = *((offset_t *) ptr - 1);
 
    /*
    * Once we have the offset, we can get our
    * original pointer and call free
    */
    void* p = (void *)((uint8_t *) ptr - offset);
 
    free (p);
}

int main()
{
    void *ptr = my_aligned_alloc (32, 32);
    printf ("Allocated at %p\n", ptr);
    printf ("Proof: %llu\n", ((unsigned long long)ptr) % 32u);
    my_aligned_free (ptr);

    return 0;
}
```

Естественно, Microsoft не могла остаться в стороне и не напортить: в Visual C++ такой функции нет, зато есть [_aligned_malloc](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/aligned-malloc?view=vs-2019), которая делает почти то же самое, только освобождать память нужно с помощью `_aligned_free`. Такие вот пироги с котятами. :(
