### GNU autotools: проверка типов

Итак, мы научились приветствовать мир с помощью autotools. Наступает черёд решения рутинных задач.

Как известно, на вкус и цвет все Unix’ы разные. Наша программа может попасть как на суперкомпьютер, так и на крохотный микроконтроллер с 64 Кб RAM. И в заголовочных файлах на машине может оказаться совсем не то, что мы ожидаем. Например, там может быть не определён какой-нибудь сильно нужный нам тип. Как нам убедиться, что в системе назначения определён, например, `size_t`?

«Всё уже украдено до нас!» В autotools заготовлены макросы для самых нужных типов: `size_t`, `int32_t` и т. д. Вот как это выглядит в файле configure.ac:

```bash
AC_INIT([hello], [1.0])
AC_CONFIG_SRCDIR([hello.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_PROG_CC

AM_INIT_AUTOMAKE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPES([ptrdiff_t])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
```

Вот какой `config.h` генерируется:

```c
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */
 
/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1
 
/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1
 
/* Define to 1 if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1
 
/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1
 
/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1
 
/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1
 
/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1
 
/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1
 
/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1
 
/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1
 
/* Name of package */
#define PACKAGE "hello"
 
/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""
 
/* Define to the full name of this package. */
#define PACKAGE_NAME "hello"
 
/* Define to the full name and version of this package. */
#define PACKAGE_STRING "hello 1.0"
 
/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "hello"
 
/* Define to the home page for this package. */
#define PACKAGE_URL ""
 
/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0"
 
/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1
 
/* Version number of package */
#define VERSION "1.0"
 
/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */
 
/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */
 
/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */
 
/* Define to the type of a signed integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int16_t */
 
/* Define to the type of a signed integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int32_t */
 
/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */
 
/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */
 
/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */
 
/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */
 
/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
 
/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */
 
/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */
 
/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */
 
/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */
 
/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
```

