### locale.h

https://ru.wikipedia.org/wiki/Locale.h

`locale.h` — заголовочный файл стандартной библиотеки языка программирования С, который используется для задач, связанных с локализацией.

#### Типы данных

Заголовочный файл объявляет структуру `lconv`, которая хранит в своих полях информацию о текущей кодировке для форматирования чисел.

#### Функции

```c
#include <locale.h>

struct lconv *localeconv (void);
char *setlocale (int category, const char *locale);
```

Функция `localeconv` получает текущую кодировку.

Функция `setlocale` устанавливает новую локализацию для операций, связанных с категорией `category` (является одной из предопределённых макросами). Стандарт определяет следующие кодировки:

* "" — локализация по умолчанию для данной платформы
* "C" — минимальная локализация для окружения языка Си
* и иные системно-зависимые.

Если запрос на изменение локализации может быть удовлетворён, функция возвращает текущую локализацию для категории `category`. В противном случае возвращается `NULL`.

При запуске программы используется "C" локализация.

Пример кода

```c
#include <stdio.h>
#include <locale.h>

int main(void)
{
  struct lconv* currentlocale;
  currentlocale = localeconv();
  printf ("In current locale standard currency symbol is %c\n", *(currentlocale->currency_symbol));
  return 0;
}
```

Пример использования функции `setlocale`

```c
#include <stdio.h>
#include <locale.h>

int main(void)
{
  setlocale (LC_ALL, "RU");
  printf ("Привет, мир!\n");
  return 0;
}
```
