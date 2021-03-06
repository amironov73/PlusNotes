### Ассемблер NASM

https://ru.wikipedia.org/wiki/NASM

NASM (Netwide Assembler) — свободный (LGPL и лицензия BSD) ассемблер для архитектуры Intel x86. Используется для написания 16-, 32- и 64-разрядных программ.

Официальный сайт: https://www.nasm.us

NASM был создан Саймоном Тэтхемом совместно с Юлианом Холлом и в настоящее время развивается небольшой командой разработчиков на SourceForge.net. Первоначально он был выпущен согласно его собственной лицензии, но позже эта лицензия была заменена на GNU LGPL после множества проблем, вызванных выбором лицензии. Начиная с версии 2.07 лицензия заменена на «упрощённую BSD» (BSD из 2 пунктов).

NASM может работать на платформах, отличных от x86, таких как SPARC и PowerPC, однако код он генерирует только для x86 и x86-64.

NASM успешно конкурирует со стандартным в Linux и многих других UNIX-системах ассемблером `gas`. Считается, что качество документации у NASM выше, чем у gas. Кроме того, ассемблер `gas` по умолчанию использует AT&T-синтаксис, ориентированный на процессоры не от Intel, в то время как NASM использует вариант традиционного для x86-ассемблеров Intel-синтаксиса; Intel-синтаксис используется всеми ассемблерами для DOS/Windows, например, MASM, TASM, fasm.

NASM поддерживает множество форматов выходных файлов, среди них:

* **bin** — файл произвольного формата, определяемого только исходным кодом. Пригоден как для файлов данных, так и для модулей с исполняемыми кодами — например, системных загрузчиков, образов ПЗУ, модулей операционных систем, драйверов `.SYS` в MS-DOS или исполняемых файлов `.COM`.
* **obj** — объектный модуль в формате OMF, совместимый с MASM и TASM.
* **win32** и **win64** — объектный модуль для 32- и 64-битного кода, совместимый с Win32- и Win64-компиляторами Microsoft.
* **aout** — объектный модуль в варианте формата a.out, использовавшемся в ранних Linux-системах.
* **aoutb** — версия формата a.out для BSD-совместимых операционных систем.
* **coff** — объектный модуль в формате COFF, совместимом с компоновщиком из DJGPP.
* **elf32** и **elf64** — объектный модуль в форматах ELF32 и ELF64, используемых в Linux и Unix System V, включая Solaris x86, UnixWare и SCO Unix.

Формат выходного файла можно задать с помощью ключа командной строки -f. Форматы могут расширять синтаксис некоторых инструкций и добавлять собственные инструкции.

«Hello world» для 32-битной Windows

```asm
EXTERN _MessageBoxA@16
EXTERN _ExitProcess@4
 
SECTION CODE USE32 CLASS=CODE
 
GLOBAL _start
_start:
    xor  eax, eax
    push eax ; MB_OK
    push title
    push banner
    xor  eax, eax
    push eax ; NULL
    call _MessageBoxA@16
 
    xor  eax, eax
    push eax ; 0
    call _ExitProcess@4
 
SECTION DATA USE32 CLASS=DATA
    banner db 'Hello, world!',0xD,0xA,0
    title db 'Hello',0
```

Как собрать (обязательно x86 Native Tools Command Prompt for VS!):

```
"C:\Program Files\NASM\nasm.exe" -f win32 hello.asm
cl hello.obj user32.lib kernel32.lib /link /entry:start /subsystem:windows
```

Получается `hello.exe` размером 3584 байт.
