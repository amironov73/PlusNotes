### Boost.Signals2

```c++
#include <iostream>
#include <boost/signals2.hpp>
 
namespace bs = boost::signals2;
 
struct Battery
{
    std::string name;
    Battery (const std::string &name_) : name { name_ } {}
 
    bs::signal <void (const std::string &)> charged;
 
    void sayCharged()
    {
        this->charged (this-> name);
    }
};
 
void handler (const std::string &name)
{
    std::cout << "Battery " << name << " is charged" << std::endl;
}
 
int main ()
{
    Battery b ("main");
    b.charged.connect (handler);
 
    std::cout << "Before\n";
    b.sayCharged();
 
    b.charged.disconnect_all_slots();
 
    std::cout << "After\n";
    b.sayCharged();
 
    return 0;
}
```
