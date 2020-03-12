### std::regex

Поиск вхождения:

```c++
#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string s = "Hello, 123, world!";
    std::regex rx (R"((\d+))");
    std::smatch sm;
    if (std::regex_search (s, sm, rx)) {
       std::cout << sm.prefix() << "|" << sm[1] << "|" << std::endl;
    }
    return 0;
}
```

Для проверки полного совпадения строки с регулярным выражением:

```c++
if (std::regex_match(text, rx)) {
    std::cout << "Match" << std::endl;
}
```

Замена:

```c++
#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string text = "Hello, 123, world!";
    std::regex rx ("world");
    std::string replacement = "planet";
    std::string modified = std::regex_replace (text, rx, replacement);
    std::cout << modified << std::endl;
    return 0;
}
```