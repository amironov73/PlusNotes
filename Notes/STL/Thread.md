### std::thread

Заголовочный файл `<thread>`. Начиная с C++11.

```c++
class thread
{ 
public:
  template <typename _Callable, typename... _Args>
  explicit thread (_Callable&& __f, _Args&&... __args) { ... }

  thread () noexcept = default;
  thread (thread&) = delete;
  thread (const thread&) = delete;
  thread (thread&& __t) noexcept { swap(__t); }
  ~thread () { if (joinable()) std::terminate(); }
  thread& operator = (const thread&) = delete;
  thread& operator = (thread&& __t) noexcept;

  void join();
  void detach();
  id get_id() const noexcept;
  native_handle_type native_handle();

  namespace this_thread
  {
    inline id get_id() noexcept;

    inline void yield() noexcept;
    template <typename _Rep, typename _Period>
    inline void sleep_for (const chrono::duration<_Rep, _Period>& __rtime);
    template <typename _Clock, typename _Duration>
    inline void sleep_until (const chrono::time_point<_Clock, _Duration>& __atime);  
};
```

Пример:

```c++
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

std::atomic_bool stop (false);

void printer ()
{
    int value = 0;

    while (!stop.load()) {
        std::cout << ++value << std::endl;
        std::this_thread::sleep_for (500ms);
    }
}

int main ()
{
    std::thread first (printer);
    first.detach ();
    std::getchar();
    stop.store(true);
    std::cout << "Done!" << std::endl;


    return 0;
}
```
