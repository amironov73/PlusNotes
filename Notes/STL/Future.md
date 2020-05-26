### std::future

https://ru.wikipedia.org/wiki/Futures_and_promises

У языка C++, как известно, начиная с версии C++11, есть будущее и обещание. Оба находятся в заголовочном файле `<future>`. Не всё же Python троллить с `from __future__ import ...` 🙂

Предлагаю простую мнемонику: «обещание исполнится в будущем». Т. е. сначала мы заводим некий объект (даём обещание), в котором пока ничего нет, кроме туманного будущего. Возле этого будущего, сидит некто, периодически интересующийся, не наступило ли то самое будущее. Когда мы положим в объект обещания хоть что-нибудь (в том числе сообщение «Не шмогла я!»), у будущее для ожидателя наступит, и он сможет забрать положенный нами объект.

```c++
template <typename Result>
class promise
{
public:
  promise ();
  promise (promise&&) noexcept;
  promise (const promise&) = delete;
  promise& operator = (const promise&) = delete;
  promise& operator = (promise&&) noexcept;
 
  future <Result> get_future();
  void set_value (const Result &value);
  void set_value_at_thread_exit (const Result &value);
  void set_exception (exception_ptr ptr);
  void set_exception_at_thread_exit (exception_ptr ptr);
};

template <typename Result>
class future
{
public:
  constexpr future() noexcept;
  future (future&&) noexcept;
  future (const future&) = delete;
  future& operator = (const future&) = delete;
  future& operator = (future&&) noexcept;
  Result get();
};
 
```

Более формальное описание: `promise` выступает в роли продюсера (производителя), а `future` в роли консьюмера (потребителя). Зачем разделили на две сущности? Чтобы скрыть от потребителя возможность записи.

Пример:

```c++
#include <iostream>
#include <thread>
#include <future>

int main ()
{
    std::promise <int64_t> calcPromise;
    auto longCalculation = [&calcPromise] {
        int64_t sum = 0;
        for (int64_t i = 0; i < 100000000; ++i) {
            sum += i;
        }
        calcPromise.set_value (sum);
    };
    std::thread computer (longCalculation);

    std::future <int64_t> calcFuture = calcPromise.get_future();
    auto patience = [&calcFuture] {
        std::cout << "Result is " << calcFuture.get() << std::endl;
    };
    std::thread user (patience);

    std::cout << "Calculating" << std::endl;

    computer.join();
    user.join();

    return 0;
}
```
