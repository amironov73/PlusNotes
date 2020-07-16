### Системные вызовы

В Linux [вызывать систему напрямую](https://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%BD%D1%8B%D0%B9_%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2) из C/C++ [легко и просто](https://www.gnu.org/software/libc/manual/html_node/System-Calls.html). Судите сами:

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
  
int main() 
{ 
    unsigned cpu, node;
  
    // Get current CPU core and NUMA node via system call
    // Note this has no glibc wrapper so we must call it directly
    syscall (SYS_getcpu, &cpu, &node, NULL);
  
    // Display information
    printf ("This program is running on CPU core %u and NUMA node %u.\n\n", 
        cpu, node);
  
    return 0;
}
```

Компилируется эта программа тривиально:

```
gcc -o callsys callsys.c
```

Всё, что нам нужно, это установленный GCC плюс знание, [какой системный вызов](https://man7.org/linux/man-pages/man2/syscalls.2.html) мы хотим дёрнуть и зачем. Вся магия сосредоточена в заголовочном файле `sys/syscall.h` (в нём собраны макросы с номерами системных вызовов) и в функции `syscall`, проживающей в `unistd.h`

```c
long int syscall (long int sysno, ...);
```

