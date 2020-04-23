### Библиотека Easylogging++

GitHub: https://github.com/amrayn/easyloggingpp

Easylogging++ is single header efficient logging library for C++ applications. It is extremely powerful, highly extendable and configurable to user’s requirements. It provides ability to write your own sinks (via featured referred as LogDispatchCallback). This library is currently used by hundreds of open-source projects on github and other open-source source control management sites.

Easylogging++ is feature-rich containing many features that both typical and advanced developer will require while writing a software;

* Highly configurable
* Extendable
* Extremely fast
* Thread and type safe
* Cross-platform
* Custom log patterns
* Conditional and occasional logging
* Performance tracking
* Verbose logging
* Crash handling
* Helper CHECK macros
* STL logging
* Send to Syslog
* Third-party library logging (Qt, boost, wxWidgets etc)
* Extensible (Logging your own class or third-party class)
* And many more…

```c++
#include "easylogging++.h"
 
INITIALIZE_EASYLOGGINGPP
 
int main(int argc, char* argv[]) {
   LOG(INFO) << "My first info log using default logger";
   return 0;
}
```
