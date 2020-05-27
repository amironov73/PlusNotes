### std::async

`std::async` — способ упрощения работы с `std::promise`. Этот вызов берет на себя создание новых потоков и получение `std::future`.

`std::async` реализована примерно так:

```c++
template<typename F>
auto async(F&& func) -> std::future<decltype(func())>
{
    typedef decltype(func()) result_type;

    auto promise = std::promise<result_type>();
    auto future  = promise.get_future();

    std::thread(std::bind([=](std::promise<result_type>& promise)
    {
        try
        {
            promise.set_value(func()); // Note: Will not work with std::promise<void>. Needs some meta-template programming which is out of scope for this question.
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    }, std::move(promise))).detach();

    return std::move(future);
}
```

Пример применения:

```c++
#include <iostream>
#include <thread>
#include <future>

int doSomething (int value)
{
    for (int i = 0; i < value; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << ".";
    }
    std::cout << std::endl;

    std::cout << "Done: " << value << std::endl;
    return value * 2;
}

int main ()
{
    auto f1 = std::async (doSomething, 100);
    std::cout << f1.get() << std::endl;

    return 0;
}
```
