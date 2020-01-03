### codecvt

Заголовочный файл `codecvt` содержит определения для шаблонных классов, умеющих конвертировать строки из одного представления в другое, например, из UTF-8 в UCS-2. Вот эти классы (там есть ещё и другие, но мы пока рассмотрим только эти):

```c++
enum codecvt_mode {
    consume_header = 4,
    generate_header = 2,
    little_endian = 1
};
 
template<class Elem,
    unsigned long Maxcode = 0x10ffff,
    codecvt_mode Mode = (codecvt_mode)0>
class codecvt_utf8;

template<class Elem,
    unsigned long Maxcode = 0x10ffff,
    codecvt_mode Mode = (codecvt_mode)0>
class codecvt_utf16;

template<class Elem,
    unsigned long Maxcode = 0x10ffff,
    codecvt_mode Mode = (codecvt_mode)0>
class codecvt_utf8_utf16;
```

Пример перекодирования из `char*` UTF-8 в `std::wstring`:

```c++
#include <iostream>
#include <string>
#include <codecvt>

int main()
{
    std::wcout.imbue(std::locale("")); // Для вывода кириллицы в консоль.

    // "Привет, мир!" в UTF-8
    char bytes[]{ 0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0,
        0xB2, 0xD0, 0xB5, 0xD1, 0x82, 0x2C, 0x20, 0xD0, 0xBC, 0xD0,
        0xB8, 0xD1, 0x80, 0x21 };

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring text = convert.from_bytes(bytes, &bytes[sizeof(bytes)]);
    std::string back = convert.to_bytes(text); // Обратно в UTF-8

    std::wcout << text << std::endl;
}
```
