### Hello 64-bit Windows на ассемблере

Чисто чтобы не забыть, как это делается.

Консольный HelloWorld для 64-битного ассемблера из комплекта поставки Visual Studio 2017 (водится, скорее всего, по адресу `C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64\ml64.exe`):

```asm
EXTRN GetStdHandle: PROC
EXTRN WriteFile:    PROC
EXTRN lstrlen:      PROC
EXTRN ExitProcess:  PROC
 
.DATA
 
    hFile        QWORD 0
    msglen       DWORD 0
    BytesWritten DWORD 0
    msg          BYTE  "Hello x64 World!", 13, 10, 0
 
.CODE
 
    main PROC
 
    ;int 3              ; breakpoint for debugger
 
    sub rsp, 28h
 
     lea rcx, msg
     call lstrlen
     mov msglen, eax
 
    mov ecx, -11        ; STD_OUTPUT
    call GetStdHandle
    mov hFile, rax
 
    lea r9, BytesWritten
    mov r8d, msglen
    lea rdx, msg
    mov rcx, hFile
    call WriteFile
 
    xor ecx, ecx        ; exit code = 0
    call ExitProcess
 
    main ENDP
 
END
```

Как это собрать? В два этапа: 1) в консоли запустить `C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat`, это настроит нужные переменные окружения, 2) следом в консоли выполнить

```
ml64 hello2.asm /link /subsystem:console /defaultlib:kernel32.lib /entry:main
```

В результате получится EXE-файл размером около 2,5 Кб (нехило так разжирел нынче ассемблер! 🙂 ).

Теперь оконный вариант:

```asm
EXTERN MessageBoxA:         PROC
EXTERN GetForegroundWindow: PROC
 
.data
 
    hello_msg db "Hello world", 0
    info_msg  db "Info", 0
 
.code
 
PUBLIC main
 
main PROC
 
    push rbp ; save frame pointer
    mov rbp, rsp ; fix stack pointer
    sub rsp, 8 * (4 + 2) ; allocate shadow register area + 2 QWORDs for stack alignment
 
    ; Get a window handle
    call GetForegroundWindow
    mov rcx, rax
 
    ; WINUSERAPI int WINAPI MessageBoxA(
    ;  RCX =>  _In_opt_ HWND hWnd,
    ;  RDX =>  _In_opt_ LPCSTR lpText,
    ;  R8  =>  _In_opt_ LPCSTR lpCaption,
    ;  R9  =>  _In_ UINT uType);
 
    mov rdx, offset hello_msg
    mov r8, offset info_msg
    mov r9, 0 ; MB_OK
 
    and rsp, not 8 ; align stack to 16 bytes prior to API call
    call MessageBoxA
 
    ; epilog. restore stack pointer
    mov rsp, rbp
    pop rbp
 
    ret
 
main ENDP
 
END
```

Собирается аналогично:

```
ml64 hello.asm /link /subsystem:windows /defaultlib:user32.lib /entry:main
```

Получается EXE-файл около 3 Кб размером.
