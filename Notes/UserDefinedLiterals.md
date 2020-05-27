### User defined literals

https://en.cppreference.com/w/cpp/language/user_literal

https://habr.com/ru/post/140357/

Введены в C++11. Пользовательские литералы поддерживаются компиляторами gcc 4.7 и clang 3.1.

Примеры литералов:

```c++
12_km;
0.5_Pa;
'c'_X;
"abc"_L;
u"xyz"_M;
```

Допускаются только такие аргументы оператора:

```c++
( const char * ) // для сырых литералов
( unsigned long long int )
( long double )
( char )
( wchar_t )
( char8_t )
( char16_t )
( char32_t )
( const char * , std::size_t ) // для подготовленных литералов
( const wchar_t * , std::size_t )
( const char8_t * , std::size_t )
( const char16_t * , std::size_t )
( const char32_t * , std::size_t )
```

Пример применения:

```c++
#include <iostream>
 
// used as conversion
constexpr double operator"" _deg (long double deg)
{
    return deg * 3.14159265 / 180.0;
}
 
// used with custom type
struct mytype
{
    unsigned long m;
};

constexpr mytype operator"" _mytype (unsigned long long int n)
{
    return mytype { n };
}
 
// used for side-effects
void operator"" _print (const char* str)
{
    // так называемый raw literal
    std::cout << str;
}
 
int main(){
    double x = 90.0_deg;
    std::cout << std::fixed << x << '\n';
    mytype y = 123_mytype;
    std::cout << y.m << '\n';
    0x123ABC_print;
}
```

Допускаются также шаблоны:

```c++
template <char... bits>
struct to_binary;

template <char high_bit, char... bits>
struct to_binary <high_bit, bits...>
{
    static_assert(high_bit == '0' || high_bit == '1', "Not a binary value!");
    static const unsigned long long value =
        (high_bit - '0') << (sizeof...(bits)) | to_binary<bits...>::value;
};

template <char high_bit>
struct to_binary <high_bit>
{
    static_assert(high_bit == '0' || high_bit == '1', "Not a binary value!");
    static const unsigned long long value = (high_bit - '0');
};

template <char... bits>
constexpr unsigned long long operator "" _b()
{
    return to_binary<bits...>::value;
}

// ...

int arr[1010_b]; // значение вычисляется во время компиляции
std::cout << 101100_b << std::endl; // выведет 44
```

В стандартной библиотеке, начиная с C++14 предусмотрены суффиксы:

* operator""s - формирование `std::basic_string<>`;
* operator""sv - формирование `std::string_view<>` (C++17);

Для комплексных чисел: `if`, `il`, `i`.

Для промежутков времени: `h`, `min`, `s`, `ss`, `us`, `ns`, `y` (C++20), `d` (C++20).
  

