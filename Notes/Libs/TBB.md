### Intel Threading Building Blocks

GitHub: https://github.com/oneapi-src/oneTBB, официальная страница: https://software.intel.com/en-us/tbb, Wikipedia: https://ru.wikipedia.org/wiki/Intel_Threading_Building_Blocks.

Intel Threading Building Blocks (также известная как TBB) — кроссплатформенная библиотека шаблонов С++, разработанная компанией Intel для параллельного программирования. Библиотека содержит алгоритмы и структуры данных, позволяющие программисту избежать многих сложностей, возникающих при использовании традиционных реализаций потоков, таких как POSIX Threads, Windows threads или Boost Threads, в которых создаются отдельные потоки исполнения, синхронизируемые и останавливаемые вручную. Библиотека TBB абстрагирует доступ к отдельным потокам. Все операции трактуются как «задачи», которые динамически распределяются между ядрами процессора. Кроме того, достигается эффективное использование кэша. Программа, написанная с использованием TBB, создаёт, синхронизирует и разрешает графы зависимостей задач в соответствии с алгоритмом. Затем задачи исполняются в соответствии с зависимостями. Этот подход позволяет программировать параллельные алгоритмы на высоком уровне, абстрагируясь от деталей архитектуры конкретной машины.

Библиотека является коллекцией шаблонов классов и функций для параллельного программирования. В библиотеке реализованы:

* параллельные алгоритмы: for, reduce, do, scan, while, pipeline, sort;
* потокобезопасные контейнеры: вектор, очередь, хеш-таблица;
* масштабируемые распределители памяти;
* мьютексы;
* атомарные операции;
* глобальная временная метка;
* планировщик задач;
* вычислительный граф.

```c++
#include “tbb/blocked_range.h”
#include “tbb/parallel_for.h”
 
#include <vector>
 
// Количество элементов вектора
const int SIZE = 10000000;
 
// Класс-обработчик
class CalculationTask
{
  std::vector<double> &myArray;
public:
  // Оператор () выполняется над диапазоном из пространства итераций
  void operator()(const tbb::blocked_range<size_t> &r) const
  {
    for (int i = r.begin(); i != r.end(); i++)
       Calculate(myArray[i]);
  }
 
  // Конструктор
  CalculationTask (const std::vector<double> &a) : myArray(a) {}
};
 
int main()
{
  std::vector<double> myArray (SIZE);
 
  // Запуск параллельного алгоритма for
  tbb::parallel_for(tbb::blocked_range<int>(0, SIZE), CalculationTask(myArray));
 
  return 0;
}
```

С использованием лямбда-функций из С++11:

```c++
#include “tbb/blocked_range.h”
#include “tbb/parallel_for.h”
 
#include <vector>
 
// Количество элементов вектора
const size_t SIZE = 10000000;
 
int main()
{
  std::vector<double> myArray (SIZE);
 
  // Запуск параллельного алгоритма for
  tbb::parallel_for (tbb::blocked_range<size_t> (0, SIZE),
  // Лямбда-функция
  [&myArray](const tbb::blocked_range<size_t> &r)
  {
     for (size_t i = r.begin(); i != r.end(); i++)
       Calculate(myArray[i]);
  });
 
  return 0;
}
```
