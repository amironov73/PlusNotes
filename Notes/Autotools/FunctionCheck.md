### GNU autotools: проверка функций

Программирование на C — это такая деятельность, где «пойти не так» может почти всё. Например, вам очень нужна какая-то функция, а на системе назначения её может просто не оказаться. «Мы тут посовещались и решили, что alloca не нужна». 🙁

Ещё хуже, когда функция есть, но определена немного по-другому или же делает что-то по-своему, а не согласно требованиям стандарта.

На этот случай предусмотрена куча макросов, вот лишь некоторые из них:

```bash
AC_FUNC_ALLOCA
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_FUNC_LSTAT
AC_FUNC_STRCOLL
AC_FUNC_STRFTIME
AC_FUNC_STRTOD
AC_FUNC_STRTOLD
AC_FUNC_STRNLEN
AC_FUNC_VPRINTF
```

Есть макрос общего назначения, проверяющий наличие определенной функции:

```bash
AC_CHECK_FUNC (function, [action-if-found], [action-if-not-found])
```

Можно проверять не отдельные функции, а целые заголовочные файлы:

```bash
AC_HEADER_ASSERT
AC_HEADER_DIRENT
AC_HEADER_STAT
AC_HEADER_STDBOOL
AC_HEADER_SYS_WAIT
AC_HEADER_TIME
```

Можно проверить скопом заголовочные файлы на соответствие стандарту C89:

```bash
AC_HEADER_STDC
```
