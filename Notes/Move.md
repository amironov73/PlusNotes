### Move-семантика

#### Что делают std::move и std::forward

Максимально упрощая — `std::move` изготавливает `&&`, чтобы изо всех перегрузок была выбрана именно с `&&`; `std::forward` предназначен для шаблонов, чтобы `&&` передалось в вызываемую из шаблона функцию. В итоге срабатывает move-семантика и убирается ненужное копирование данных при вызове. Вот и всё.

```c++
#include <iostream>
#include <string>
 
void func (int &i)
{
    std::cout << "&" << std::endl;
}
 
void func (int &&i)
{
    std::cout << "&&" << std::endl;
}
 
template <class T> void wrapper1 (T t)
{
    func (t);
}
 
template <class T> void wrapper2 (T t)
{
    func (std::forward<T> (t));
}
 
int main()
{
    int i = 0;
    func (1);                     // &&
    func (i);                     // &
    func (std::move(1));          // &&
    func (std::move(i));          // &&
    func (std::forward<int>(1));  // &&
    func (std::forward<int>(i));  // &&
    wrapper1 (1);                 // &
    wrapper1 (i);                 // &
    wrapper2 (1);                 // &&
    wrapper2 (i);                 // &&
 
    return 0;
}
```
