### SFINAE

SFINAE — особая шаблонная магия C++.

SFINAE (англ. substitution failure is not an error, «неудавшаяся подстановка — не ошибка») — механизм языка C++, связанный с шаблонами и перегрузкой функций.

Правило SFINAE гласит: **Если не получается рассчитать окончательные типы аргументов (провести подстановку шаблонных параметров) перегруженной шаблонной функции, компилятор не выбрасывает ошибку, а ищет другую подходящую перегрузку.** Ошибка будет в трёх случаях:

* Не нашлось ни одной подходящей перегрузки.
* Нашлось несколько таких перегрузок, и Си++ не может решить, какую взять.
* Перегрузка нашлась, она оказалась шаблонной, и при инстанцировании шаблона случилась ошибка.

В результате у нас появляется возможность создать варианты шаблонных классов или функций, рассчитанных на разные случаи жизни, а компилятор будет выбирать нужный вариант, ориентируясь на заботливо написанные нами «подсказки».

От нас требуется написать что угодно, лишь бы возникала ошибка подстановки во всех случаях, кроме нужного нам (например, переданный шаблону тип-аргумент является целочисленным).

Применение SFINAE облегчают две вещи: `std::enable_if` и [type traits](Types.md).

Структура `std::enable_if` определена примерно так:

```c++
template<bool B, class T = void>
struct enable_if {};
  
template<class T>
struct enable_if<true, T> { typedef T type; };
```

Эта структура нужна лишь для одной цели: у неё то есть, то нет `typedef T type`, и это зависит от первого параметра шаблона.

А сформулировать условие для `std::enable_if` нам помогут type traits, ведь они предоставляют замечательные методы для проверки самых разных свойств типов.

В результате идея выглядит так: Есть вышеописанная структура `std::enable_if`. Если мы передаем в её шаблон `true`, у неё появится `::type`, иначе структура останется пустой. Нужное нам условие мы получаем вызовом соответствующего шаблона type trais. А затем сошлёмся на `::type`. Если нужное нам условие не выполняется, мы ссылаемся на несуществующий ::type, возникает нужная нам ошибка подстановки, и компилятор переходит к другому варианту шаблона. Но один из вариантов не выдаст ошибки подставновки, и это (надеемся) окажется нужный нам вариант.

Вот пример, как мы можем этого сделать:

```c++
#include <iostream>
#include <type_traits>
 
template <typename T>
typename std::enable_if <std::is_integral<T>::value>::type 
func (T value) // по факту возвращает void
{
   std::cout << value << ": integer" << std::endl;
}
 
template <typename T>
typename std::enable_if <std::is_floating_point<T>::value>::type 
func (T value) // по факту возвращает void
{
   std::cout << value << ": float" << std::endl;
}
 
int main ()
{
    func (5u);
    func (3.14);
    return 0;
}
 
// 5: integer
// 3.14: float
```

В этом месте C#-программисты немного завидуют, т. к. подобных ограничений на аргументы generic-типов задать невозможно. 🙂

Обратите внимание: SFINAE не смотрит внутрь тела функций. Её интересует только заголовок. Если что-то не заладится с телом, то возникнет обычная ошибка компиляции, перехода к другому варианту не произойдёт.
