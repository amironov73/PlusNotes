### Монада Maybe

Вдохновленный [записью в блоге Дмитрия Нестерука](https://nesteruk.wordpress.com/2015/12/24/maybe-monad-cpp/), я наваял свою версию монады Maybe, совместимую с C++11.

[Согласно Википедии](https://ru.wikipedia.org/wiki/%D0%9C%D0%BE%D0%BD%D0%B0%D0%B4%D0%B0_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5)), монада — это абстракция линейной цепочки связанных вычислений. Монады позволяют организовывать последовательные вычисления.

Самая, наверное, известная из монад – Maybe, которая решает простую, но важную задачу: что делать, если необходимое нам для вычислений значение не задано? Ответ прост: ничего не делать, а вернуть специальное значение, которое означает «значение не задано». Вот как это иллюстрируется:

```
data Maybe T  =  Just T or Nothing
 
add : (Maybe Number left, Maybe Number right) -> Maybe Number
     if left is Nothing then
         Nothing
     else if right is Nothing then
         Nothing
     else
         Just (left + right)
     end if
```

Вот и я сделал, наверное, миллион первую обёртку над указателем с гордым названием `Maybe<T>`, которая ничего не делает, если указатель равен `nullptr`. :)

```c++
#include <iostream>
#include <string>
#include <type_traits>

// предварительное объявление шаблона, 
// чтобы можно было сослаться на него в функции maybe
template <class T> struct Maybe;
 
/// \brief Создание монады.
template <class T>
Maybe<T> maybe (T *context)
{
    return Maybe<T> { context };
}
 
/// \brief Шаблон монады.
template <class T>
struct Maybe final
{
    T *context; ///< Контекст (хранимый указатель).

    /// Конструктор.
    explicit Maybe (T *context_) noexcept : context { context_ } {}
    Maybe (const Maybe<T>&) = default;
    Maybe (Maybe<T> &&other) noexcept
        : context (other.context) { other.context = nullptr; }
    Maybe<T>& operator = (const Maybe<T>&) = default;
    Maybe<T>& operator = (Maybe<T> &&other) noexcept
    {
        if (&other != this) {
            this->context = other.context;
            other.context = nullptr;
        }
        return *this;
    }

    /// \brief Обращение к члену класса.
    template <class Func>
    auto operator & (Func func) -> decltype (maybe (func (this->context)))
    {
        using ReturnType = typename std::result_of <Func(T*)>::type;
        using WithoutPointer = typename std::remove_pointer <ReturnType>::type;
        if (this->context) {
            return maybe(func (this->context));
        }
        return maybe <WithoutPointer> (nullptr);
    }

    /// \brief Вызов функции.
    template <class Func>
    Maybe<T>& operator | (Func func)
    {
        if (this->context) {
            func (context);
        }
        return *this;
    }
};

/// \brief Вывод в поток
template <class T>
std::ostream& operator << (std::ostream &stream, const Maybe<T> &value)
{
    if (value.context) {
        stream << *(value.context);
    }
    return stream;
}

// Пример применения

struct Address
{
    std::string *city;
};
 
struct Person
{
    Address *address;
};
 
int main() {
    auto *address = new Address;
    address->city = new std::string ("Irkutsk");
    auto *person = new Person;
    person->address = address;
 
    auto m = maybe (person)
            & [] (Person *p) { return p->address; }
            & [] (Address *a) { return a->city; }
            | [] (std::string *s) { std::cout << *s << "\n"; }
            ;
    std::cout << "City is: " << m << std::endl;
 
    return 0;
}
```

Древний g++ 4.8.5 не ругается, всё успешно компилируется и выполняется. Это радует.
