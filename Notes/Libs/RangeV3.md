### Библиотека Range v3

Range-v3 — это универсальная библиотека, которая дополняет существующую стандартную библиотеку средствами для работы с диапазонами. О диапазоне можно свободно думать о паре итераторов, хотя их не нужно реализовывать таким образом. Объединение начальных и конечных итераторов в один объект дает несколько преимуществ: удобство, возможность компоновки и корректность.

Homepage: https://ericniebler.github.io/range-v3/<br/>
GitHub: https://github.com/ericniebler/range-v3<br/>
YouTube: https://youtu.be/mFUXNMfaciE

```c++
#include <iostream>
#include <vector>
#include <algorithm>
 
#include "range/v3/algorithm/count.hpp"
#include "range/v3/algorithm/count_if.hpp"
 
#include "range/v3/view/filter.hpp"
#include "range/v3/view/transform.hpp"
 
using ranges::views::filter;
using ranges::views::transform;
 
int main() {
    const auto input = std::vector<int>{1, 2, 3, 4, 5};
     
    const auto c1 = ranges::count (input, 4);
    std::cout << "count: " << c1 << std::endl;
 
    const auto c2 = ranges::count_if (input, [] (int x) { return x % 2 == 0; });
    std::cout << "count_if: " << c2 << std::endl;
     
    std::vector<int> output1;
    std::copy_if ( std::begin (input), std::end (input),
            std::back_inserter (output1),
            [] (int x) { return x % 2 != 0; });
 
    std::cout << "back_inserter: ";
    for (const auto item : output1) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
 
    std::cout << "filter: ";
    auto output2 = input | filter ([](int i) { return i % 2 != 0;});
    for (const auto item : output2) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
 
    std::cout << "transform: ";
    auto output3 = input 
       | filter ([](int i) { return i % 2 != 0;})
       | transform ([](int i) { return i * 10; });
    for (const auto item : output3) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
 
    return 0;
}
 
// count: 1
// count_if: 2
// back_inserter: 1 3 5
// filter: 1 3 5
// transform: 10 30 50
```
