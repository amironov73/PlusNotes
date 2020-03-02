### Dynamic Linking Library

#### Спецификация \_\_declspec(dllexport)

Выглядит так:

```c++
// для отдельной функции
__declspec(dllexport) void __cdecl Function1(void);

// для класса
class __declspec(dllexport) ExampleClass : public CObject
{ 
    // ... class definition ... 
};
```

По факту добавляет в OBJ-файл указание:
 
```
#pragma comment(linker, "/export:Function1")
``` 
 
В свою очередь это добавляет в командную строку линкеру link.exe следующий фрагмент:

```
/EXPORT:Function1
```

#### Спецификация \_\_declspec(dllimport)

Выглядит так:

```c++
// для переменной
__declspec(dllimport) int accumulator;

// для отдельной функции 
__declspec(dllimport) int calculate();

// для класса
class __declspec(dllimport) ExampleClass : public CObject
{
    // ... class definition ...
};
```

В принципе, работать должно без `__declspec`, в этом случае компилятор сгенерирует код вроде такого:

```asm
push    2               ; uCmd
push    esi             ; hWnd
call    GetWindow
mov     esi, eax
...

; HWND __stdcall GetWindow(HWND hWnd, UINT uCmd)
GetWindow       proc
                jmp     ds:__imp_GetWindow
GetWindow       endp
...
; HWND __stdcall GetWindow(HWND hWnd, UINT uCmd)
extrn __imp_GetWindow:dword
```

С `__declspec` компилятор сгенерирует код

```asm
call DWORD PTR __imp_GetWindow
...

; HWND __stdcall GetWindow(HWND hWnd, UINT uCmd)
extrn __imp_GetWindow:dword
```

Код получается быстрее и меньше.

#### DLL, собранные разными версиями компилятора

Отвечает [Кодт](http://rsdn.org/forum/cpp.applied/3315654.1)

Проблем может быть дофигища самых разнообразных, поэтому лучше договориться — как избегать проблем.

Недекорированные имена.
Разные компиляторы декорируют по-разному, поэтому экспортировать/импортировать нужно, либо объявляя extern "C", либо вообще .def-файлами.
Естественно, что перегрузка здесь обламывается.

Менеджеры памяти (в составе CRT).
Не надеяться на то, что они общие для всех — даже компилируя с опциями "(Debug) (Multithreaded) DLL". Для разных версий компилятора рантаймы разные.
Поэтому никаких выделений памяти в одном месте и утилизации в другом — только всё своими силами.
Соответственно, библиотека, отдающая наружу свежесозданный объект (да хоть строку), должна использовать одну из техник:
— экспортировать функции утилизации
— протащить функцию утилизации через интерфейс объекта (например, COM — IUnknown::Release)
— использовать менеджер памяти ОС (например, COM — SysAllocString, CoTaskMemAlloc и т.д.)

Использовать стандартные конвенции — cdecl и stdcall. Всякие fastcall могут реализовываться по-разному даже у одного компилятора в зависимости от ключа оптимизации.

Если сишный API слишком узок, использовать COM. Необязательно, что это будет полноценный inproc server, можно и легковесные (без регистрации коклассов). Все виндоузные компиляторы совместимы с COM.
Более общий С++ный ООП не экспортировать — могут быть разные лэяуты, разные конвенции thiscall, дубликаты статических переменных...

Не кидать исключения за пределы своего модуля. Даже сквозь колбэк-функцию