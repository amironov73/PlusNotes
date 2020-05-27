### Hello 64-bit Linux на ассемблере

По аналогии с Windows сделаем Hello World для 64-битной Linux. Поскольку синтаксис гнутого ассемблера меня выворачивает на изнанку, применим NASM, который при необходимости устанавливается в одну команду:

```
# apt-get-install nasm
```

Итак, текст hello.s:

```asm
global _start
 
section .text
 
_start:
  mov rax, 1        ; write(
  mov rdi, 1        ;   STDOUT_FILENO,
  mov rsi, msg      ;   "Hello, world!\n",
  mov rdx, msglen   ;   sizeof("Hello, world!\n")
  syscall           ; );
 
  mov rax, 60       ; exit(
  mov rdi, 0        ;   EXIT_SUCCESS
  syscall           ; );
 
section .rodata
 
  msg: db "Hello, world!", 10
  msglen: equ $ - msg
```

Как это собрать:

```
> nasm -f elf64 -o hello.o hello.s
> ld -o hello hello.o
> ./hello
```

Получается ELF-файл размером около 800 байт (прямо даже завидно как-то становится, в Windows EXE-файл втрое жирнее).
