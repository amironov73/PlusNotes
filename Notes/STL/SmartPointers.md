### Умные указатели

Заголовочный файл `<memory>`. Начиная с C++ 11.

#### unique_ptr

Указатель, владеющий объектом и не желающий делиться владением.

```c++
template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;
```

Специальная утилитная функция `make_unique` (начиная с C++ 14):

```c++
template< class T, class... Args >
unique_ptr<T> make_unique( Args&&... args ); // создаёт указатель на единичный объект

template< class T >
unique_ptr<T> make_unique( std::size_t size ); // массив объектов заданного размера.
```

#### shared_ptr

Указатель, владеющий объектом и допускающий существование других владельцев.

```c++
template< class T > class shared_ptr;
```

Специальная утилитная функция `make_shared`:

```c++
template< class T, class... Args >
shared_ptr<T> make_shared( Args&&... args ); // начиная с C++ 11
```

#### weak_ptr

Слабая ссылка на `shared_ptr` (не увеличивающая счётчик).

```c++
template< class T > class weak_ptr;
```
