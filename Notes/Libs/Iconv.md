### Библиотека iconv

Насколько легко конвертировать в .NET данные из одной кодировки в другую, настолько же заморочно это делать в неуправляемом мире 🙁 В.NET нам достаточно вызвать метод Encoding.Convert, а в C/C++ для начала придётся поискать подходящую библиотеку.

Ладно, библиотеку мы нашли: это GNU iconv, пришедшая к нам из мира Unix. Есть старая статья с алгоритмом сборки в Visual Studio, но можно не заморачиваться, а взять готовые DLL отсюда: https://github.com/pffang/libiconv-for-Windows.

Теперь надо научиться пользоваться ею.

```c++
#include <iostream>
#include <string>
 
#include "iconv.h"
#pragma comment(lib, "libiconv.lib")
 
std::string convert(const char *fromCP, const char *toCP,
    const std::string &text)
{
    iconv_t cd = iconv_open(toCP, fromCP);
    if (cd == iconv_t(-1))
    {
        throw std::exception("Can't open ICONV");
    }
 
    const char *inputbuffer = text.data();
    size_t inputlen = text.size();
    size_t outputlen = (inputlen + 1) * 4;
    char *outbuffer = static_cast<char*>(malloc(outputlen));
    if (!outbuffer)
    {
        iconv_close(cd);
        throw std::exception("Can't allocate memory");
    }
 
    memset(outbuffer, 0, outputlen);
    char *outptr = outbuffer;
    const size_t retcode = iconv(cd, &inputbuffer, &inputlen, 
       &outptr, &outputlen);
    iconv_close(cd);
    if (retcode == size_t(-1))
    {
        free(outbuffer);
        throw std::exception("Can't convert");
    }
 
    std::string result (outbuffer);
    free(outbuffer);
    return result;
}
 
int main(char **argv, int argc)
{
    const std::string srcMsg("У попа была собака");
    const std::string dstMsg = convert("CP1251", "CP866", srcMsg);
    std::cout << dstMsg;
 
    return 0;
}
```
 
Для конверсии в Unicode сочиняем аналогичную функцию:

```c++
std::wstring convertWide(const char *fromCP, const char *toCP,
    const std::string &text)
{
    iconv_t cd = iconv_open(toCP, fromCP);
    if (cd == iconv_t(-1))
    {
        throw std::exception("Can't open ICONV");
    }
 
    const char *inputbuffer = text.data();
    size_t inputlen = text.size();
    size_t outputlen = (inputlen + 1) * 4;
    char *outbuffer = static_cast<char*>(malloc(outputlen));
    if (!outbuffer)
    {
        iconv_close(cd);
        throw std::exception("Can't allocate memory");
    }
 
    memset(outbuffer, 0, outputlen);
    char *outptr = outbuffer;
    const size_t retcode = iconv(cd, &inputbuffer, &inputlen, 
       &outptr, &outputlen);
    iconv_close(cd);
    if (retcode == size_t(-1))
    {
        free(outbuffer);
        throw std::exception("Can't convert");
    }
 
    std::wstring result (reinterpret_cast<wchar_t*>(outbuffer));
    free(outbuffer);
    return result;
}
```
 
и конвертировать так:

```c++
const std::string srcMsg("У попа была собака");
const std::wstring wideMsg = convertWide("CP1251", "UCS-2LE", srcMsg);
std::wcout << wideMsg << std::endl;
```
