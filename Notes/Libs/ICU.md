### International Components for Unicode

International Components for Unicode (ICU) -- это проект с открытым исходным кодом библиотек C/C++ и Java для поддержки Unicode, интернационализации и глобализации программного обеспечения. ICU переносится на многие операционные системы. Он дает приложениям одинаковые результаты на всех платформах, а также между программным обеспечением C, C ++ и Java. Проект ICU является техническим подразделением Консорциума Unicode и спонсируется, поддерживается и используется IBM и многими другими компаниями.

Официальный сайт: [http://www.icu-project.org](http://www.icu-project.org/). GitHub: [https://github.com/unicode-org/icu](https://github.com/unicode-org/icu). Wikipedia: [https://en.wikipedia.org/wiki/International_Components_for_Unicode](https://en.wikipedia.org/wiki/International_Components_for_Unicode).

Собрать и пакетировать можно с помощью vcpkg:

```
> vcpkg install icu:x64-windows
> vcpkg integrate project
```

После этого можно смело идти в `Tools` -> `NuGet Package Manager` -> `Package Manager Console` и вбивать туда

```
Install-Package vcpkg.D.Vcpkg -Source "D:\Vcpkg\scripts\buildsystems"
```

Visual Studio как по волшебству подключает нужные заголовочные файлы и подсовывает линкёру нужные библиотеки. Главное тут не запутаться в отладочном/релизном/статическом/динамическом режимах сборки и, конечно же, в x86/x64.

И ещё, как обычно, лучше не рисковать, подсовывая в проект на MSVC 2019 библиотеку, собранную в MSVC 2017, и наоборот. Может страшно [заглючить самым гадким образом](http://rsdn.org/forum/cpp.applied/3315654.1).

Для нас самым интересным в ICU является заголовочный файл `ucnv.h`, т. к. он содержит низкоуровневые функции перекодировки символов из/в Unicode.

```c++
#include <iostream>

#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

int main()
{
    UChar messageUC[] {
        L'П', L'р', L'и', L'в', L'е', L'т', L',', L' ',
        L'м', L'и', L'р', L'!'
    };
    char bufferAnsi[100];

    UErrorCode status = U_ZERO_ERROR;
    UConverter *converter = ucnv_open("cp1251", &status);
    if (!U_SUCCESS(status)) {
        exit(-1);
    }

    status = U_ZERO_ERROR;
    int32_t len = ucnv_fromUChars(converter, bufferAnsi, sizeof(bufferAnsi), 
        messageUC, sizeof(messageUC)/sizeof(UChar), &status);
    if (!U_SUCCESS(status)) {
        exit(-1);
    }

    std::cout << len << ": " << bufferAnsi << std::endl;

    memset(bufferAnsi, 0, sizeof(bufferAnsi));
    char messageAnsi[] { 0xCF, 0xF0, 0xE8, 0xE2, 0xE5, 0xF2, 0x2C, 0x20,
        0xEC, 0xE8, 0xF0, 0x21 };
    UChar bufferUC[100];
    memset(bufferUC, 0, sizeof(bufferUC));

    status = U_ZERO_ERROR;
    len = ucnv_toUChars(converter, bufferUC, sizeof(bufferUC) / sizeof(UChar),
        messageAnsi, sizeof(messageAnsi), &status);
    if (!U_SUCCESS(status)) {
        exit(-1);
    }

    icu::UnicodeString text(bufferUC);
    std::cout << len << ": " << text << std::endl;
    
    ucnv_close(converter);
}
```

