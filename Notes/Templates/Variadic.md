### Шаблоны с переменным числом параметров

Раньше я, полагаясь на свой опыт в C, лепил функции переменного числа аргументов примерно так:

```c++
// за эллипсисом скрываются разрешённые коды возврата
bool checkReturnCode (int nargs, ...)
{
    va_list args;
    auto result = true;
 
    auto rc = getReturnCode();
    if (rc < 0) {
        va_start (args, nargs);
        result = false;
        for(auto i = 0; i < nargs; i++) {
            const int code = va_arg (args, int);
            if (code == rc) {
                result = true;
                break;
            }
        }
        va_end (args);
    }
 
    return result;
}
```

Это худо-бедно работало, но пришла пора освоить магию шаблонов.

Сначала классический способ: рекурсивный шаблон.

```c++
#include <iostream>
 
struct S
{
    template<typename T>
    void print (T t)
    {
        std::cout << t << std::endl;
    }
 
    template <typename T1, typename... T2>
    void print (T1 t1, T2... t2)
    {
        print (t1);
        print (t2...);
    }
};
 
int main()
{
    S s;
 
    // вызов функции одного переменного
    s.print (1);
    s.print ("Hello");
    s.print (true);
    s.print (2.5);
 
    std::cout << "===========" << std::endl;
 
    // вызов вариадической функции
    // фактически раскрывается в последовательность вызовов
    s.print (1, "Hello", true, 2.5);
 
    // вызов с пустым перечнем аргументов невозможен
    // s.print (); // ошибка компиляции
}
```
Если аргументы функции одного типа, то можно положить их в список инициализации и работать с ним привычными range for или sizeof:

```c++
#include <iostream>
 
struct S
{
    template <typename... T>
    void printMany (std::string prefix, T... many)
    {
        std::cout << prefix << ' ';
        const auto list = { many... };
        for (const auto one : list) {
            std::cout << one << ' ';
        }
        std::cout << std::endl;
    }
};
 
int main()
{
    S s;
    s.printMany ("PI:", 3.14);
    s.printMany ("Number:", 2, 12, 85, 06);
    //s.printMany ("Nothing:"); // ошибка компиляции
}
```

Вариант, подсмотренный у Jason Turner:

```c++
#include <iostream>
#include <utility>

template<typename T>
static void print_ (const T &t)
{
    std::cout << t << '\n';
}

template<typename ... T>
void print (const T& ... t)
{
    (void)std::initializer_list<int> { (print_ (t), 0)... };
}

int main()
{
    print ("Hello", "World", 1, 2, 3, 5.1);
    return 0;
}
```

Всё вышеизложенное работает, начиная с C++11.
