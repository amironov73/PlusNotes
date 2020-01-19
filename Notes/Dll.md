### Dynamic Linking Library

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