### Intrinsic

Если хочется сделать что-нибудь, что не предусмотрено языком C/C++, в ход идёт ассемблер. Visual C++ с незапамятных времён предоставляет для этих целей ключевое слово <code>_asm</code>. Например, вот так можно перемножить два массива чисел с плавающей точкой.

```c++
#include <cstdio>

int main()
{
    float source1[4] { 1.0f, 2.0f, 3.0f, 4.0f };
    float source2[4] { 5.0f, 6.0f, 7.0f, 8.0f };
    float result[4] { 0 };

    // умножаем вектор source1 на source2
    // результат помещаем в result
    _asm {
        movups xmm1, source1
        movups xmm2, source2
        mulps  xmm1, xmm2
        movups result, xmm1
    }

    printf ("%f, %f, %f, %f\n", result[0], result[1], result[2], result[3]);

    return 0;
}
```

К сожалению, поддерживается это только для режима x86. :(

Но не будем унывать! Нормальные герои всегда идут в обход! Если нельзя использовать ассемблер, воспользуемся "свойственными" функциями, т. е. [intrinsic](https://docs.microsoft.com/ru-ru/cpp/intrinsics/compiler-intrinsics?view=vs-2019). Это специальные обёртки над инструкциями процессора, их формальные объявления находятся в заголовочном файле `intrin.h`.

```c++
#include <cstdio>
#include <intrin.h>

int main()
{
    int data[4] { 0 };
    char name[16] { 0 };
    __cpuid (data, 0);
    // к сожалению, приходится перекладывать байты в правильном порядке
    *(int*)(&name[0]) = data[1];
    *(int*)(&name[4]) = data[3];
    *(int*)(&name[8]) = data[2];
    printf ("Processor: %s\n", name); // у меня вывело ожидаемо GenuineIntel
    return 0;
}
```

Сделаем теперь что-нибудь более полезное, например, перемножим два вектора, как в первом примере.

```c++
#include <cstdio>
#include <intrin.h>

int main()
{
    auto first  = _mm_set_ps ( 1.0f, 2.0f, 3.0f, 4.0f);
    auto second = _mm_set_ps ( 5.0f, 6.0f, 7.0f, 8.0f);
    auto result = _mm_mul_ps (first, second);
    printf ("%f, %f, %f, %f\n", result.m128_f32[3], 
        result.m128_f32[2], result.m128_f32[1], 
        result.m128_f32[0]);
    return 0;
}
```

Эта программа работает уже и в режиме x86, и в режиме x64.
