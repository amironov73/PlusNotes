### codecvt

Заголовочный файл `codecvt` содержит определения для шаблонных классов, умеющих конвертировать строки из одного представления в другое, например, из UTF-8 в UCS-2. Вот эти классы (там есть ещё и другие, но мы пока рассмотрим только эти):

```c++
enum codecvt_mode {
    consume_header = 4,
    generate_header = 2,
    little_endian = 1
};

template<
    class InternT,
    class ExternT,
    class State
> class codecvt;
 
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

Пример перекодирования из UTF-8 в `std::wstring` и обратно:

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

Опосредованно эти классы используются в `<locale>`. Пример преобразования из однобайтной кодировки в `std::wstring` и обратно:

```c++
#include <iostream>
#include <string>
#include <locale>

std::string narrow(const std::wstring &wide, const std::locale &loc)
{
    std::string result;
    const auto length = wide.length();
    if (!length) {
        return result;
    }

    result.resize(length);
    const auto start = wide.data();
    const auto stop = start + length;
    const auto buffer = const_cast<char*>(result.data());
    std::use_facet<std::ctype<wchar_t>>(loc).narrow(start, stop, '?', buffer);

    return result;
}

std::wstring widen(const std::string &str, const std::locale &loc)
{
    std::wstring result;
    const auto length = str.length();
    if (!length) {
        return result;
    }

    result.resize(length);
    const auto start = str.data();
    const auto stop = start + length;
    const auto buffer = const_cast<wchar_t*>(result.data());
    std::use_facet<std::ctype<wchar_t>>(loc).widen(start, stop, buffer);

    return result;
}

int main()
{
    //const std::locale loc(".866");
    const std::locale loc(".1251");
    const std::wstring ws1(L"Привет, мир!");

    std::string s1 = narrow(ws1, loc);
    std::cout &lt;&lt; s1 &lt;&lt; std::endl;

    std::wstring ws2 = widen(s1, loc);
    std::wcout &lt;&lt; ws2 &lt;&lt; std::endl;
}
```
