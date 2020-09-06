### Turbo Assembler

https://ru.wikipedia.org/wiki/TASM

Turbo Assembler (TASM) — программный пакет компании Borland, предназначенный для разработки программ на языке ассемблера для архитектуры x86. Кроме того, TASM может работать совместно с трансляторами с языков высокого уровня фирмы Borland, такими как Turbo C и Turbo Pascal. Как и прочие программные пакеты серии Turbo, TASM больше не поддерживается.

Пакет TASM поставляется вместе с компоновщиком Turbo Linker и создаёт объектный .obj-файл, который компоновщик переводит в исполнимый файл. Полученные исполнимые файлы можно отлаживать с помощью Turbo Debugger.

По умолчанию TASM работает в режиме совместимости с другим распространённым ассемблером — Microsoft Macro Assembler, то есть TASM умеет транслировать исходники, разработанные под MASM. Кроме того, TASM имеет режим IDEAL, улучшающий синтаксис языка и расширяющий его функциональные возможности.

Пример программы для MS-DOS на TASM

```asm
.MODEL TINY
CODE SEGMENT
ASSUME CS:CODE, DS:CODE
ORG 100h
START:
        mov ah,9
        mov dx,OFFSET Msg
        int 21h
        int 20h
        Msg DB 'Hello World',13,10,'$'
CODE ENDS
END START
```

Пример программы для MS-DOS на TASM в режиме IDEAL

```asm
IDEAL
MODEL TINY
CODESEG
STARTUPCODE
        mov ah,9
        lea dx,[Msg]
        int 21h
        int 20h
Msg     DB 'Hello World',13,10,'$'
END
```
