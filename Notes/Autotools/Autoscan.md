### Autoscan

За годы своего существования autotools успели утомить довольно много программистов по всему миру. Утомлённые написанием однообразных `configure.ac` пользователи сели и написали скрипт `autoscan`, который создаёт более-менее пригодные «болванки».

Вот пример. Допустим, у нас есть проект с такой структурой:

```
project
├── app
│   └── hello.c
├── include
│   └── something.h
└── lib
    └── something.c
```

Запускаем в корне проекта `autoscan` и получаем `configure.scan` следующего содержания:

```
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
 
AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([app/hello.c])
AC_CONFIG_HEADERS([config.h])
 
# Checks for programs.
AC_PROG_CC
 
# Checks for libraries.
 
# Checks for header files.
 
# Checks for typedefs, structures, and compiler characteristics.
 
# Checks for library functions.
 
AC_OUTPUT
```

Согласитесь, вполне себе автоматизация. 🙂
