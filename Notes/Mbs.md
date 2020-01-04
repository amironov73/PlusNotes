### Мультибайтовые строки

Заголовочный файл `<cstdlib>`.

```c++
int mblen(const char* s, std::size_t n);
int mbtowc(wchar_t* pwc, const char* s, std::size_t n);
int wctomb(char *s, wchar_t wc);
std::size_t mbstowcs(wchar_t* dst, const char* src, std::size_t len);
std::size_t wcstombs(char* dst, const wchar_t* src, std::size_t len);
```