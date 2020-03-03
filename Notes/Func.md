### \_\_func\_\_

`__func__` - предопределённый идентификатор, включенный в C99 и в C++11. Он содержит имя текущей функции.

```c++
#include <iostream>

int main()
{
  std::cout << "In function " << __func__ << std::endl;
}
```

[См. документацию Microsoft.](https://docs.microsoft.com/ru-ru/cpp/cpp/func?view=vs-2019)
