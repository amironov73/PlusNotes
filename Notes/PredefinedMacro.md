### Предопределенные макросы в компиляторах C/C++

https://sourceforge.net/p/predef/wiki/Home/

Как определить, каким компилятором обрабатывается наш код? С помощью предопределенных макросов:

```c++
#if defined (_MSC_VER)
// code specific to Visual Studio compiler
#endif
```

Добрые люди собрали в одном месте такие макросы.

#### Определение операционной системы

```
Linux and Linux-derived           __linux__
Android                           __ANDROID__ (implies __linux__)
Linux (non-Android)               __linux__ && !__ANDROID__
Darwin (Mac OS X and iOS)         __APPLE__
Akaros (http://akaros.org)        __ros__
Windows                           _WIN32
Windows 64 bit                    _WIN64 (implies _WIN32)
NaCL                              __native_client__
AsmJS                             __asmjs__
Fuschia                           __Fuchsia__
FreeBSD                           __FreeBSD__
NetBSD                            __NetBSD__
OpenBSD                           __OpenBSD__
DragonFly                         __DragonFly__
AIX                               __AIX
Solaris                           __sun или __SVR4
HP-UX                             __hpux
```

#### Стандарт C++

Согласно стандарту C++ (п.14.8) макрос `__cplusplus` должен быть определен компилятором и соответствовать версии поддерживаемого стандарта:

```c++
C++ pre-C++98:  #define __cplusplus 1
C++98:          #define __cplusplus 199711L
C++98 + TR1:    #define __cplusplus 199711L // ???
C++11:          #define __cplusplus 201103L
C++14:          #define __cplusplus 201402L
C++17:          #define __cplusplus 201703L
```

#### Определение компилятора

https://sourceforge.net/p/predef/wiki/Compilers/

```
ARM                             __CC_ARM
Borland                         __BORLANDC__, __CODEGEARC__
Clang                           __clang__
Comeau C++                      __COMO__
Compaq C/C++                    __DECC, __DECCXX, __VAXC, VAXC
Coverity C/C++ Static Analyzer  __COVERITY__
Cray C                          _CRAYC
Digital Mars                    __DMC__
DJGPP                           __DJGPP__, __GO32__
EDG C++ Frontend                __EDG__
Emscripten                      __EMSCRIPTEN__ (for asm.js and webassembly)
GCC                             __GNUC__
IAR C/C++                       __IAR_SYSTEMS_ICC__
Intel C/C++                     __INTEL_COMPILER. __ICC, __ECC, __ICL. __INTEL_COMPILER
KAI C++                         __KCC
KEIL CARM                       __CA__, __KEIL__
LCC                             __LCC__
LLVM                            __llvm__
MetaWare High C/C++             __HIGHC__
Metrowerks CodeWarrior          __MWERKS__, __CWCC__
MinGW 32                        __MINGW32__
MinGW-w64 32bit                 __MINGW32__
MinGW-w64 64bit                 __MINGW64__
Small Device C Compiler         SDCC
Symantec C++                    __SC__
Tiny C                          __TINYC__
Turbo C/C++                     __TURBOC__
Ultimate C/C++                  _UCC
USL C                           __USLC__
Visual Studio                   _MSC_VER
Watcom                          __WATCOMC__
Zortech                         __ZTC__
```

#### Версии компилятора

**GCC:**

```c++
#if defined(__GNUC__) && (__GNUC___ > 5 || (__GNUC__ == 5 && __GNUC_MINOR__ >= 1))
// this is gcc 5.1 or greater
#endif
```

Под GCC можно ещё узнать архитектуру процессора:

```c++
__i386__
__x86_64__
__arm__. If defined, you can further check:
  __ARM_ARCH_5T__
  __ARM_ARCH_7A__
__powerpc64__
__aarch64__
```

**Clang**

Clang: `__clang_major__, __clang_minor__, __clang_patchlevel__`.

**MinGW**

MinGW 32-bit: `__MINGW32_MAJOR_VERSION` and `__MINGW32_MINOR_VERSION`
MinGW 64-bit: `__MINGW64_VERSION_MAJOR` and`__MINGW64_VERSION_MINOR`

**Visual Studio:**

```
VS                        _MSC_VER   _MSC_FULL_VER
1                         800
3                         900
4                         1000
4                         1020
5                         1100
6                         1200
6 SP6                     1200    12008804
7                         1300    13009466
7.1 (2003)                1310    13103077
8 (2005)                  1400    140050727
9 (2008)                  1500    150021022
9 SP1                     1500    150030729
10 (2010)                 1600    160030319
10 (2010) SP1             1600    160040219
11 (2012)                 1700    170050727
12 (2013)                 1800    180021005
14 (2015)                 1900    190023026
14 (2015 Update 1)        1900    190023506
14 (2015 Update 2)        1900    190023918
14 (2015 Update 3)        1900    190024210
15 (2017 Update 1 & 2)    1910    191025017
15 (2017 Update 3 & 4)    1911
15 (2017 Update 5)        1912
```

**Watcom:**

Watcom C++ 10.5: `#define __WATCOMC__ 1050`
Watcom C++ 11.0: `#define __WATCOMC__ 1100`
Open Watcom 1.0: `#define __WATCOMC__ 1200`
Open Watcom 1.9: `#define __WATCOMC__ 1290`

**ARM Compiler:**

Realview C 3.0: `#define __ARMCC_VERSION 300503`

**Borland:**

| Borland C++ | C++ Builder | `__BORLANDC__` | `__CODEGEARC__`
|-------------|-------------|----------------|--------------- 
| 2.0         |             | 0x200          |
| 3.0         |             | 0x400          |
| 3.1         |             | 0x410          |
| 4.0         |             | 0x452          |
| 5.0         |             | 0x500          |
| 5.02        | 1.0         | 0x52           |
|             | 3.0         | 0x530          |
|             | 4.0         | 0x540          |
| 5.5         | 5.0         | 0x550          |
| 5.51        |             | 0x551          |
| 5.6.4       |             | 0x562          |
|             | 2006        | 0x570          | 0x570
|             | 2007        | 0x590          | 0x590
|             | 2009        | 0x613          | 0x613
|             | 2010        | 0x621          | 0x621
|             | XE          | 0x630          | 0x630
|             | XE2         | 0x640          | 0x640
|             | XE3         | 0x650          | 0x650
|             | XE4         | 0x660          | 0x660

| Turbo C | Turbo C++ | `__TURBOC__`
|---------|-----------|-------------
| 2.01    |           | 0x201
|         | 1.00      | 0x295
|         | 1.01      | 0x296
|         | 2.00      | 0x297

**Comeau C++:**

Comeau C++ 2.3: `#define __COMO_VERSION__ 230`

**Digital Mars:**

Digital Mars | `__DMC__`
-------------|----------
7.0          | 0x700
7.2          | 0x720
8.0          | 0x800

**Intel C/C++:**

Intel C/C++ | `__INTEL_COMPILER` | `__INTEL_COMPILER_BUILD_DATE`
------------|--------------------|------------------------------
5.0         | 500                |
6.0         | 600                |
8.0         | 800                |
9.0         | 900                | 20060222

