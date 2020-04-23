### libcurl для C/C++

Кроме C#-обёртки над cURL, конечно же, есть и нативная библиотечка, которую можно использоваться в своих проектах на C/C++. Её домашняя страничка: https://curl.haxx.se/libcurl/, там же можно взять как скомпилированный вариант под множество платформ, так и исходные тексты. Впрочем, собрать libcurl самостоятельно – дело пяти минут, основную нагрузку берут на себя скрипты, любезно предоставленные авторами. От нас же требуется лишь вызвать CMake, который вызовет эти скрипты в нужной последовательности.

Допустим, мы собрали релизную версию `libcurl.dll`, как теперь использовать это сокровище в своём проекте? А вот как. Создаём пустую папку, в которую помещаем файл `CMakeLists.txt` следующего содержания:

```cmake
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
 
project(learnCurl)
 
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)
link_libraries(libcurl_imp.lib)
 
add_executable(learnCurl main.cpp)
```

В поддиректорию `libs` кладём `libcurl_imp.lib`, полученный в результате компиляции библиотеки, а в поддиректорию `include/curl` все h-файлы из папки `include/curl` оригинальной библиотеки.

Пишем файл `main.cpp` следующего содержания:

```c++
#include <cstdio>
#include "curl/curl.h"
 
// Пользовательская функция, вызываемая из libcurl, когда с сервера 
// загружена очередная порция данных. 
// Она просто сохраняет данные в указанный файл.
static size_t write_data (void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite (ptr, size, nmemb, (FILE *)stream);
    return written;
}
 
int main() {
    CURL *curl = curl_easy_init();
    if(curl) {
        FILE *file = fopen ("homepage.htm", "wb");
        if (file) {
            curl_easy_setopt (curl, CURLOPT_URL, "http://example.com");
            curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt (curl, CURLOPT_WRITEDATA, file);
            CURLcode retcode = curl_easy_perform (curl);
            fclose (file);
        }
        curl_easy_cleanup(curl);
    }
 
    return 0;
}
```

Зовём CMake, получаем `learnCurl.exe`, рядом с которым нужно положить `libcurl.dll`, и можно запускать. Вуаля! Мы только что скачали файл с помощью libcurl.

Если всё, что нам нужно — записать данные в файл, можно обойтись без пользовательской функции вроде write_data. Можно просто передать указатель на файл в библиотеку:

```c++
FILE *file = fopen ("homepage.htm", "wb");
if (file) {
    curl_easy_setopt (curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt (curl, CURLOPT_FILE, file);
    CURLcode retcode = curl_easy_perform (curl);
    fclose (file);
}
```

В примере выше я использовал так называемый упрощенный интерфейс, когда файлы скачиваются по одному, без особенных заморочек. Для тех, кому этого мало, существует полноценный интерфейс библиотеки, называемый multi.

При необходимости можно собрать статическую версию libcurl и не таскать с собой `libcurl.dll`:

```
> cmake.exe -D BUILD_SHARED_LIBS=OFF -D CURL_DISABLE_LDAP=ON -D CMAKE_BUILD_TYPE=Release ..
> cmake.exe --build . --config Release
```

Здесь я отключил в libcurl поддержку LDAP, т. к. она всё равно мне не нужна. Вы можете отключить что-нибудь ещё. 🙂
