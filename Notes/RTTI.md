### RTTI

https://habr.com/ru/post/470265/

*Run-Time Type Information. Идентификация типа во время исполнения.* Это механизм, позволяющий получить информацию о типе объекта или выражения во время выполнения. Существует и в других языках, а в C++ он используется для:

* `dynamic_cast`
* `typeid` и `type_info`
* перехвата исключений

Важное ограничение: RTTI использует таблицу виртуальных функций, и, следовательно, работает только для полиморфных типов (виртуального деструктора достаточно). Важное пояснение: `dynamic_cast` и `typeid` не всегда используют RTTI, поэтому работают и для неполиморфных типов. Например, для динамического приведения ссылки на потомка к ссылке на предка RTTI не нужен, вся информация доступна во время компиляции.

RTTI не дается бесплатно, пусть немного, но он отрицательно влияет на производительность и размер потребляемой памяти (отсюда частый совет не использовать `dynamic_cast` из-за его медлительности). Поэтому компиляторы, как правило, позволяют отключить RTTI. GCC и MSVC обещают, что на корректности перехвата исключений это не скажется.
