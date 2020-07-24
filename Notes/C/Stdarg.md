### stdarg.h

https://ru.wikipedia.org/wiki/Stdarg.h

**stdarg.h** — заголовочный файл стандартной библиотеки языка программирования Си, предоставляющий средства для перебора аргументов функции, количество и типы которых заранее не известны.

Содержимое `stdarg.h` часто используют в функциях с произвольным количеством аргументов (к примеру, `printf`, `scanf`).

Заголовочный файл определяет тип `va_list` и набор функций для операций над ним: `va_start`, `va_arg`, `va_copy` (C99), `va_end`.

```c
#include <stdarg.h>
type va_arg   (va_list ap, type);
void va_copy  (va_list dest, va_list src);
void va_end   (va_list ap);
void va_start (va_list ap, parmN);
```

Макрос `va_start` служит для инициализации списка переменных аргументов и должен иметь соответствующий вызов `va_end`. Макрос `va_arg` используется для получения доступа к очередному аргументу, а `va_copy` - для копирования объектов типа `va_list`.

#### Пример

```c
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void var (char *format, ...)
{
	va_list ap;
	va_start (ap, format);
	if(!strcmp (format, "%d"))
	{
		int x = va_arg (ap, int);
		printf ("You passed decimal object with value %d\n", x);
	}

	if(!strcmp(format, "%s"))
	{
		char *p = va_arg (ap, char *);
		printf ("You passed c-string \"%s\"\n", p);
	}
	va_end (ap);
}

int main (void)
{
	var ("%d", 255);
	var ("%s", "test string");
	return 0;
}
```
