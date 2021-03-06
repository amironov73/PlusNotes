### NULL

https://ru.wikipedia.org/wiki/NULL_(%D0%A1%D0%B8)

`NULL` в языках программирования Си и C++ — макрос, объявленный в заголовочном файле `stddef.h` (и других заголовочных файлах). Значением этого макроса является зависящая от реализации константа нулевого указателя (англ. null pointer constant).

Константа нулевого указателя — это целочисленное константное выражение со значением 0 или (только в Си) такое же выражение, но приведённое к типу void*. Константа нулевого указателя, приведённая к любому типу указателей, является нулевым указателем. Гарантируется, что нулевой указатель не равен указателю на любой объект (в широком смысле слова, любые данные) или функцию. Гарантируется, что любые два нулевых указателя равны между собой. Разыменовывание нулевого указателя является операцией с неопределённым поведением.

Иначе говоря, реализация предоставляет специальное значение — константу нулевого указателя, которую можно присвоить любому указателю и такой указатель при сравнении не будет равен любому «корректному» указателю. То есть, можно считать, что нулевой указатель не содержит корректного адреса в памяти.

#### Использование

Нулевые указатели придуманы как удобный способ «отметить» указатели, которые заведомо не указывают на корректный адрес в памяти. Например, при объявлении указателя как автоматической переменной его значение не определено. Чтобы отметить, что этот указатель ещё не содержит корректный адрес в памяти, такому указателю присваивают константу нулевого указателя:

```c
void f(void)
{
  int *x = NULL;
  /* ... */
}
```

Хорошим стилем программирования является присваивание указателю после освобождения памяти, на которую он ссылался, нулевого указателя. Кроме этого, применение обнуления указателей актуально для безопасности освобождения памяти: операция `delete` в C++ (`free` в Си) безопасна для нулевого указателя. Например:

```c++
TYPE *foo = new TYPE();
// использование foo
delete foo; // foo != NULL
// некоторый код программы
delete foo; // ОШИБКА! память уже недоступна
```

в то время как в таком варианте ошибки не будет

```c++
TYPE *foo = new TYPE();
//использование foo
delete foo; // foo != NULL
foo = NULL; // foo == NULL
// некоторый код программы
delete foo; // ошибки нет: delete проверяет значение foo
```

#### Размерность указателя

При вызове функции в один из аргументов может быть передан `NULL`. Макрос `NULL` в разных компиляторах может быть определен различными способами, в том числе

```c
#define NULL 0

#define NULL ((void *)0)
```

В первом случае `NULL` имеет тип `int`, а во втором случае - тип `void*`. Существуют архитектуры, где `sizeof(int) != sizeof(void*)`, тогда на разных платформах в функцию будет приходит разное количество байт, что может нарушить её работу. В настоящее время предпринимается попытка решить эту проблему в Си путём введения `nullptr`, см предложение N 2394.

#### Разыменовывание нулевых указателей

Разыменовывание нулевого указателя является операцией с неопределённым поведением. На реализацию не накладывается никаких ограничений: может произойти, например, обращение к памяти, не предназначенной для использования данной программой (то есть при чтении будет считан «мусор», а при записи — значение будет записано в область памяти, не принадлежащую программе). Например, в DOS запись по нулевому адресу затрёт как минимум нулевой вектор прерываний, так что следующий вызов `int 0` приведёт, скорее всего, к зависанию системы. Однако чаще всего это приводит к ошибке времени выполнения (если в операционной системе реализована защита памяти и доступ в невыделенную процессу память блокируется). Например, в Windows 9x сообщение «Общая ошибка защиты» — «Программа выполнила недопустимую операцию и будет закрыта» (англ. general protection fault, GPF) выдаётся чаще всего в тех случаях, когда программа обращается в память по некорректному (в том числе неинициализированному или уже освобождённому) указателю. В Unix-подобных операционных системах в таких ситуациях процесс получает сигнал `SIGSEGV` и его обработчик выводит сообщение «Segmentation fault».

#### Нулевые указатели в C++

Если брать конкретную реализацию `NULL` по исходным файлам, то он может быть определен как `(void*)0` или как `0`. Использование `NULL` в проектах на языке C++ может приводить к ошибкам. Например

```c++
int (ClassName::*pf)() = NULL;
```

приведет к ошибке компиляции в случае, если `NULL` определен как `(void*)0` (например опосредованно был включен заголовок, где стандартное для C++ определение `NULL` перекрывается). Поэтому в программах на C++ не рекомендуется использовать `NULL`. В стандарте C++11 для обозначения нулевого указателя добавлено новое ключевое слово `nullptr`.
