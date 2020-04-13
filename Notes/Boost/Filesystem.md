### Boost.Filesystem

```c++
#include <iostream>
#include <boost/filesystem.hpp>
 
namespace fs = boost::filesystem;
 
int main (int argc, char **argv)
{
    fs::path program (argv[0]);
    std::cout << std::boolalpha;
    std::cout << "Path " << program <<" exist: "
        << fs::exists(program) << std::endl;
    std::cout << "Is regular file: "
        << fs::is_regular_file (program) << std::endl;
    std::cout << "Size is: " << fs::file_size (program) 
        << std::endl;
 
    auto directory = program.parent_path();
    for (auto child : directory) {
        std::cout << "\t" << child << std::endl;
    }
 
    return 0;
}
```
