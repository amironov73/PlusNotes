### Утилита Premake

Для OpenSource-проектов бывает необходимо предоставлять с исходными текстами сборочные скрипты (в случае Visual Studio – файлы проектов) для разных платформ и разных версий инструментария (для той же Visual Studio 2005/2008/2010/2012 и т. д.). Конечно же, все необходимые скрипты можно создать и поддерживать вручную, но это утомительно и чревато ошибками. Гораздо лучше иметь один «главный скрипт», согласно которому по мере надобности изготавливаются скрипты для конкретных сочетаний платформы и версии инструментария.

Одним из инструментов, предоставляющих такую возможность, является [Premake](http://premake.github.io/). Он позволяет описать проект на языках C/C++/C# таким образом, чтобы необходимые сборочные скрипты формировались автоматически. Поддерживаются следующие среды разработки:

* Visual Studio 2002-2019, включая Express-версии;
* GNU Make, включая Cygwin and MinGW;
* Apple Xcode;
* Code::Blocks;
* CodeLite;
* IC#Code SharpDevelop;
* MonoDevelop.

Поддерживаются платформы:

* Windows 32- и 64-бит;
* Mac OS X 32- и 64-бит;
* Playstation 3 (Visual Studio и GNU Make);
* Xbox 360 (только Visual Studio);
* Linux 32- и 64-бит.

Кроме того, Premake предоставляет Lua-скриптинг, который расширяет возможности по обработке конфигураций буквально любой сложности.

Исходные коды Premake: https://github.com/premake, ссылка для скачивания: http://premake.github.io/download.html

Premake представляет собой небольшую (около 300 Кб в версии для Windows) консольную утилиту с простым синтаксисом вызова:

```
premake4 [действие]
```

Действие | Описание
---------|---------
vs2013 | Visual Studio 2013
vs2012 | Visual Studio 2012
vs2010 | Visual Studio 2010
vs2008 | Visual Studio 2008
vs2005 | Visual Studio 2005
vs2003 | Visual Studio 2003
vs2002 | Visual Studio 2002
gmake  | GNU make (в т. ч. Cygwin и MinGW)
xcode3 | Apple XCode 3
codeblocks | Code::Blocks
codelite | CodeLite
clean | Удалить все сгенерированные файлы
—cc=gcc | Выбор компилятора C++:<br/>gcc — GNU gcc/g++<br/> ow — Open Watcom
—dotnet=msnet | Выбор платформы .Net:<br/> msnet — Microsoft .Net (csc)<br/>mono — Mono (mcs)<br>pnet — Portable .Net (cscc)
—file=filename | Считывать скрипт из указанного файла. По умолчанию premake4.lua
—os=windows | Выбор операционной системы:<br/>windows — Microsoft Windows<br/>bsd — OpenBSD/NetBSD/FreeBSD
haiku — Haiku<br/>linux — Linux<br/>macosx — Apple MacOS X<br/>solaris — Solaris
—platform=x32 | Выбор архитектуры:<br/>x32 — 32-битная (в т. ч. x86)<br/>x64 — 64-битная<br/>universal — универсальная MacOS X (32 + 64)<br/>universal32 — универсальная MacOS X, только 32 бита<br/>universal64 — универсальная MacOS X, только 64 бита<br/>ps3 — Playstation 3<br/>xbox360 — Xbox 360
—scripts=path | Искать скрипты по указанному пути
—version | Показать информацию о версии

Пример простого скрипта для консольного приложения HelloWorld на C#:

```lua
#!lua
 
solution "HelloWorld"
   configurations { "Debug", "Release" }
 
   project "HelloWorld"
      kind "ConsoleApp"
      language "C#"
      files { "Hello.cs" }
 
      configuration "Debug"
         defines { "DEBUG", "TRACE" }
         flags { "Symbols" }
 
      configuration "Release"
         defines {}
         flags { "Optimize" }
```

Теперь о полезных мелочах: 🙂

Задать папку, в которой будут генерироваться файлы проектов:

```lua
solution "HelloWorld"
   location "build/"
 
   project "HelloWorld"
       location "build/"
```

Добавление файлов в проект:

```lua
files {
   "hello.h",  -- можно задать конкретные имена файлов
   "*.c",      -- можно использовать маски файлов
   "**.cpp"    -- рекурсивное добавление файлов
}
excludes { 
    "tests/*.c",  -- исключаем все тесты
    "**/Win32Specific/**" -- и всё Windows-специфичное
}
```

Где искать заголовочные файлы:

```lua
includedirs { 
    "../lua/include", 
    "../zlib"
}
```

Добавление библиотек и ссылок на фреймворки/проекты:

```lua
libdirs { 
   "libs", -- где искать библиотеки
   "../mylibs" 
}
links { 
   "zlib", -- подключаем указанную библиотеку (c/c++)
   "Cocoa.framework", -- фреймворк
   "MyLibraryProject" -- ссылка на проект в солюшене
}
```

Платформы (x86/x64):

```lua
solution "HelloWorld"
    platforms { "x32" }
 
    project "HelloWorld"
        platforms { "x32" }
```

Флаги для компилятора:

Flag | Description
-----|------------
EnableSSE | Use the SSE instruction set for floating point math.
EnableSSE2 | Use the SSE2 instruction set for floating point math.
ExtraWarnings | Sets the compiler’s maximum warning level.
FatalWarnings | Treat warnings as errors.
FloatFast | Enable floating point optimizations at the expense of accuracy.
FloatStrict | Improve floating point consistency at the expense of performance.
Managed | Enable Managed C++ (.NET) features.
MFC | Enable support for Microsoft Foundation Classes.
NativeWChar, NoNativeWChar | Enable or disable support for the wchar data type. If no flag is specified, the toolset default will be used.
No64BitChecks | Disable 64-bit portability warnings.
NoEditAndContinue | Disable support for Visual Studio’s Edit-and-Continue feature.
NoExceptions | Disable C++ exception support.
NoFramePointer | Disable the generation of stack frame pointers.
NoIncrementalLink | Disable support for Visual Studio’s incremental linking feature.
NoImportLib | Prevent the generation of an import library for a Windows DLL.
NoManifest | Prevent the generation of a manifest for Windows executables and shared libraries.
NoMinimalRebuild | Disable Visual Studio’s minimal rebuild feature.
NoPCH | Disable precompiled header support. If not specified, the toolset default behavior will be used.
NoRTTI | Disable C++ runtime type information.
NoRuntimeChecks | Disable Visual Studio’s \[default stack frame and uninitialized variable checks\]
OptimizeSize | Optimize for the smallest file size.
OptimizeSpeed | Optimize for the best performance.
SEH | Enable structured exception handling.
StaticRuntime | Perform a static link against the standard runtime libraries.
Symbols | Generate debugging information.
Unicode | Enable Unicode strings. If not specified, the default toolset behavior is used.
Unsafe | Enable the use of unsafe code in .NET applications.
WinMain | Use WinMain() as the program entry point for Windows applications, rather than the default main().

Виды приложений для директивы kind:

* **ConsoleApp**: консольное приложение.
* **WindowedApp**: десктопное приложение.
* **SharedLib**: динамическая библиотека (DLL).
* **StaticLib**: статическая библиотека (LIB).

Задание фреймворка .NET:

```lua
solution "HelloWorld"
    framework "3.5"
 
    project "HelloLib"
         framework "4.0"
```

Действия перед и после сборки:

```lua
prebuildcommands { "commands" }
postbuildcommands { "copy default.config bin\\project.config" }
```

Отладочная печать в процессе генерации сборочных скриптов:

```lua
printf("format", ...)
```
 
Условная конструкция:

```lua
result = iif(os.is("windows"), "is windows", "is not windows")
```
 
Форматирование строки:

```
local ver = os.getversion()
print(string.format(" %d.%d.%d (%s)", 
   ver.majorversion, ver.minorversion, ver.revision,
   ver.description))
```

Premake основана на Lua, и её сборочный скрипт по факту является необычно выглядящим скриптом Lua. Пользователю доступны все имеющиеся в Lua средства: переменные, выражения, функции и т. д. Пример использования переменной:

```lua
local lang = "C++"
language (lang)  -- используем переменную, скобки обязательны
 
workspace("HelloWorld" .. _ACTION) -- конкатенация строк, скобки обязательны
```

Иерархия в сборочном скрипте: элементы, определённые в глобальном контексте, автоматически включаются в контекст солюшена. Элементы, определённые в контексте солюшена, автоматически включаются в контекст проекта. Элементы, определённые в контексте проекта, автоматически включаются в контекст конфигурации. Пример:

```lua
-- Глобальный контекст, определение будет включено во все солюшены
defines { "GLOBAL" }
 
workspace "MyWorkspaces"
  -- Контекст солюшена наследует глобальному
  -- Определения будут: { "GLOBAL", "WORKSPACE" }
  defines { "WORKSPACE" }
 
project "MyProject"
  -- Контекст проекта наследует солюшену
  -- Определения будут: { "GLOBAL", "WORKSPACE", "PROJECT" }
  defines { "PROJECT" }
```

Пример скрипта, активно использующего наследование по иерархии:

```lua
#!lua
 
language "C#"
kind "ConsoleApp"
configurations { "Debug" }
targetname "HelloWorld"
files { "src/*.cs", "src/*.resx" }
links { "System", "System.Data", "System.Xml" }
 
configuration "Debug"
    defines { "DEBUG" }
    flags { "Symbols" }
 
workspace "HelloWorld"
    location "build"
 
    project "HelloWorld.net20"
        location "build/net20"
        dotnetframework "2.0"
 
    project "HelloWorld.net35"
        location "build/net35"
        dotnetframework "3.5"
        links { "System.Core" }
 
    project "HelloWorld.net40"
        location "build/net40"
        dotnetframework "4.0"
        links { "System.Core" }
 
    project "HelloWorld.net45"
        location "build/net45"
        dotnetframework "4.5"
        links { "System.Core", "System.Threading" }
```

Немного о поддержке NuGet. По адресу https://github.com/aleksijuvani/premake-nuget находится расширение, которое добавляет в Premake поддержку NuGet. Пример скрипта:

```lua 
require "nuget"

solution "MySolution"
    configurations { "release", "debug" }
 
    project "FirstProject"
        kind "ConsoleApp"
        language "C++"
        files "main.cpp"
        nuget { "boost:1.59.0-b1", "sdl2.v140:2.0.3", 
           "sdl2.v140.redist:2.0.3" }
 
    project "AnotherProject"
        kind "ConsoleApp"
        language "C#"
        files "main.cs"
        nuget "Newtonsoft.Json:7.0.1"
```

Однако, на данный момент расширение почему-то не работает. 🙁

