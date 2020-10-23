### Ключевое слово restrict

C99 подарил нам [новое ключевое слово](https://ru.wikipedia.org/wiki/Restrict) [restrict](https://en.cppreference.com/w/c/language/restrict). Как правило, его применяют к аргументам функции:

```c
int somefunc (int *restrict ptr) ...
```

Модификатор `restrict` накладывает на указатель `P` следующее ограничение: если объект, на который ссылается указатель `P`, меняется любым способом, то все обращения к этому объекту должны происходить только через этот указатель `P`, иначе компилятор поведение не определено.

Если объект по ограниченной ссылке никак не модифицируется, то у него могут быть псевдонимы, т. е. другие (тоже ограниченные!) указатели, ссылающиеся на этот объект.

Ограниченные указатели можно спокойно присваивать обычным.

Ограниченные указатели были введены ради оптимизации. Рассмотрим следующую функцию:

```c
void function (int *arg1, int *arg2, int *delta)
{
    *arg1 += *delta;
    *arg2 += *delta;
}
```

GCC10 в режиме `-O2 -std=c99` генерирует для неё следующий код:

```asm
function:
    mov     eax, DWORD PTR [rdx]
    add     DWORD PTR [rdi], eax
    mov     eax, DWORD PTR [rdx]
    add     DWORD PTR [rsi], eax
    ret
```

Однако, если ограничить указатель `delta`

```c
void function (int *arg1, int *arg2, int *restrict delta)
{
    *arg1 += *delta;
    *arg2 += *delta;
}
```
то генерируется более эффективный код:

```c
function:
    mov     eax, DWORD PTR [rdx]
    add     DWORD PTR [rdi], eax
    add     DWORD PTR [rsi], eax
    ret
```

В данном случае `restrict` говорит компилятору, что значение, на которое указывает `delta`, можно не загружать в регистр повторно, т. к. программист гарантирует, что оно не меняется. Если эта гарантия не выполняется, программа имеет полное право начать «глючить».

Конечно же, `restrict` можно применять не только к аргументам функций. Вот пример применения к переменным:

```c
float *restrict a, *restrict b;
float c[100];

int init(int n) {
    float * t = malloc (2 * n * sizeof (float));
    a = t;      // a refers to 1st half
    b = t + n;  // b refers to 2nd half
}
// compiler can deduce from the restrict qualifiers that
// there is no potential aliasing among the names a, b, and c
```

Вот пример применения к полю структуры:

```c
// Restricted pointers assert that
// members point to disjoint storage.
struct t {
    int n;
    float *restrict p;
    float *restrict q;
};
```

Нельзя применять `restrict` к указателям на функции.

GCC в дополнение к `restrict` распознает также `__restrict` и `__restrict__` (оба работают и в режиме C++). Clang в дополнение к `restrict` распознает только `__restrict__` (работает и в C++). Open Watcom поддерживает `restrict`, начиная с версии 1.3 (только со включенной опции `-za99`).

Microsoft, конечно же, не могла остаться безучастной, и немного подгадила. Visual C++ не признает ключевого слова restrict, ему подавай __restrict. Зато оно работает и в режиме C++. Ну хоть так :)

Чисто для справки. Visual C++ 19 генерирует следующий код:

```asm
; void function (int *arg1, int *arg2, int *delta)
function PROC
    mov     eax, DWORD PTR [r8]
    add     DWORD PTR [rcx], eax
    mov     eax, DWORD PTR [r8]
    add     DWORD PTR [rdx], eax
    ret     0
function ENDP

; void function (int *arg1, int *arg2, int *__restrict delta)
function PROC
    mov     eax, DWORD PTR [r8]
    add     DWORD PTR [rcx], eax
    add     DWORD PTR [rdx], eax
    ret     0
function ENDP
```
