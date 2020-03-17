### Типы данных

#### Фундаментальные типы

* `void` -- нужен для `void*`.

* `char`, `unsigned char` и `signed char` -- разные типы! `char` тоже считается целочисленным типом, просто для него можно задавать литералы в виде `'A'`.

* `wchar_t` -- тип для широких символов. Может иметь разный размер в разных реализациях (как 2 байта, так и 4). `wchar_t` тоже целочисленный тип (см. выше).

* `char16_t` и `char32_t` -- тоже типы для широких символов, но с известным размером. Начиная с C++ 11.

* `char8_t` -- для строк в UTF-8. Начиная с C++ 20.

* `bool` -- имеет ровно два значения: `true` и `false`.

* Целочисленные типы: `short int`, `int`, `long int` и `long long int` (последний -- начиная с C++ 11). У всех, кроме `int` суффикс `int`  можно опустить (чаще всего так и поступают).

```
1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
```

К целочисленным типам можно прицепить префиксы `unsigned` или `signed`. Если нет префикса, считается, что неявно прицеплен `signed`.

В Windows x86: `sizeof(int) == sizeof(long) == sizeof(void*) == 4`. В Windows x64: `sizeof(int) == sizeof(long) == 4; sizeof(void*) == 8`. В Unix x64: `sizeof(int) == 4; sizeof(long) == sizeof(void*) == 8`.

* Типы с плавающей точкой: `float` (обычно 32 бита), `double` (64 бита) и `long double` (80 бит).

#### Важные и нужные типы

* `size_t` -- беззнаковое целое, возвращаемое `sizeof(something)`. Обычно имеет тот же размер, что и указатель на данной платформе.

* `ptrdiff_t` -- знаковое целое, используемое для хранения разности двух указателей. Обычно имеет тот же размер, что и указатель на данной платформе.

* `nullptr_t` -- тип для `nullptr`.

* `intptr_t` и `uintptr_t` -- целое (знаковое и беззнаковое), вмещающее в себя указатель на данной платформе.

#### Челочисленные типы фиксированной ширины

Введены, начиная с C++ 11. Заголовочный файл `<cstdint>`.

* `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`. 

* `int_fast8_t`, `int_fast16_t`, `int_fast32_t`, `int_fast64_t`, `uint_fast8_t`, `uint_fast16_t`, `uint_fast32_t`, `uint_fast64_t`.

* `int_least8_t`, `int_least16_t`, `int_least32_t`, `int_least64_t`, `uint_least8_t`, `uint_least16_t`, `uint_least32_t`, `uint_least64_t`.  

#### type traits

type traits — специальный раздел стандартной библиотеки, предназначенная для шаблоностроителей. Она создаётся авторами компиляторов, а прикладные программисты могут только пользоваться ей. Добавить или поправить в ней что-либо не в наших силах.

Предусмотрена куча шаблонов, выдающих самую разнообразную информацию об указанном типе (паре типов).

```c++
#include <iostream>
#include <type_traits>
 
template<class T, class U>
void typeChecker (T arg1, U arg2)
{
    std::cout << "is void="
        << std::is_void<T>::value << std::endl;
    std::cout << "is null="
        << std::is_null_pointer<T>::value << std::endl;
    std::cout << "is integral="
        << std::is_integral<T>::value << std::endl;
    std::cout << "is float="
        << std::is_floating_point<T>::value << std::endl;
    std::cout << "is array="
        << std::is_array<T>::value << std::endl;
    std::cout << "is enum="
        << std::is_enum<T>::value << std::endl;
    std::cout << "is union="
        << std::is_union<T>::value << std::endl;
    std::cout << "is class="
        << std::is_class<T>::value << std::endl;
    std::cout << "is function="
        << std::is_function<T>::value << std::endl;
    std::cout << "is lvalue ref="
        << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is rvalue ref="
        << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is member object pointer="
        << std::is_member_object_pointer<T>::value << std::endl;
    std::cout << "is member function pointer="
        << std::is_member_function_pointer<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "is fundamental="
              << std::is_fundamental<T>::value << std::endl;
    std::cout << "is arithmetic="
              << std::is_arithmetic<T>::value << std::endl;
    std::cout << "is scalar="
              << std::is_scalar<T>::value << std::endl;
    std::cout << "is object="
              << std::is_object<T>::value << std::endl;
    std::cout << "is compound="
              << std::is_compound<T>::value << std::endl;
    std::cout << "is reference="
              << std::is_reference<T>::value << std::endl;
    std::cout << "is member_pointer="
              << std::is_member_pointer<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "is const="
              << std::is_const<T>::value << std::endl;
    std::cout << "is volatile="
              << std::is_volatile<T>::value << std::endl;
    std::cout << "is trivial="
              << std::is_trivial<T>::value << std::endl;
    std::cout << "is trivially copyable="
              << std::is_trivially_copyable<T>::value << std::endl;
    std::cout << "is standard layout="
              << std::is_standard_layout<T>::value << std::endl;
    std::cout << "is pod="
              << std::is_pod<T>::value << std::endl;
    std::cout << "is empty="
              << std::is_empty<T>::value << std::endl;
    std::cout << "is polymorphic="
              << std::is_polymorphic<T>::value << std::endl;
    std::cout << "is abstract="
              << std::is_abstract<T>::value << std::endl;
    std::cout << "is final="
              << std::is_final<T>::value << std::endl;
    std::cout << "is signed="
              << std::is_signed<T>::value << std::endl;
    std::cout << "is unsigned="
              << std::is_unsigned<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "is constructible="
              << std::is_constructible<T>::value << std::endl;
    std::cout << "is trivially constructible="
              << std::is_trivially_constructible<T>::value << std::endl;
    std::cout << "is nothrow constructible="
              << std::is_nothrow_constructible<T>::value << std::endl;
    std::cout << "is default constructible="
              << std::is_default_constructible<T>::value << std::endl;
    std::cout << "is copy constructible="
              << std::is_copy_constructible<T>::value << std::endl;
    std::cout << "is move constructible="
              << std::is_move_constructible<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "is assignable="
              << std::is_assignable<T, U>::value << std::endl;
    std::cout << "is trivially assignable="
              << std::is_trivially_assignable<T, U>::value << std::endl;
    std::cout << "is nothrow assignable="
              << std::is_nothrow_assignable<T, U>::value << std::endl;
    std::cout << "is copy assignable="
              << std::is_copy_assignable<T>::value << std::endl;
    std::cout << "is move assignable="
              << std::is_move_assignable<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "is destructible="
              << std::is_destructible<T>::value << std::endl;
    std::cout << "is trivially destructible="
              << std::is_trivially_destructible<T>::value << std::endl;
    std::cout << "is nothrow destructible="
              << std::is_nothrow_destructible<T>::value << std::endl;
    std::cout << "has virtual destructor="
              << std::has_virtual_destructor<T>::value << std::endl;
 
    std::cout << "===================" << std::endl;
 
    std::cout << "rank="
              << std::rank<T>::value << std::endl;
    std::cout << "is same="
              << std::is_same<T, U>::value << std::endl;
    std::cout << "is base of="
              << std::is_base_of<T, U>::value << std::endl;
    std::cout << "is convertible="
              << std::is_convertible<T, U>::value << std::endl;
}
 
int main()
{
    typeChecker (1, 'a');
    return 0;
}
```

Проверять результат, выдаваемый type traits, в рантайме скучно. Хотелось бы проверять различные характеристики типов на этапе компиляции и соответственно выбирать вариант кода.

type traits отлично подходят для [SFINAE](Sfinae.md).
