### Библиотека Catch2

Catch2 -- кроссплатформенная библиотека юнит-тестирования, отличающаяся повышенной простотой применения. Она помещается в одном (правда, довольно большом) заголовочном файле. В настоящее время используется вторая версия библиотеки, ориентированная стандарт C++11 и выше. Предыдущая, первая версия, ориентировалась на стандарт C++03.

GitHub: [https://github.com/catchorg/Catch2](https://github.com/catchorg/Catch2). Официальный сайт [http://catch-lib.net](http://catch-lib.net) просто редиректит на GitHub.

Добавить Catch2 в свой проект очень просто: достаточно скачать из раздела релизов на GitHub файл `catch.hpp` (625 Кб) и положить его куда-нибудь, куда Вы складываете заголовочные файлы. Можно воспользоваться [ночной сборкой](https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp). Есть также вариант [интеграции с CMake](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository).

Если библиотека была инсталлирована с помощью менеджера пакетов или CMake, ссылаться на неё следует так: `#include &lt;catch2/catch.hpp&gt`, если скачана вручную, то `#include "catch.hpp"`.

Попробуем затеять с помощью CLion небольшое юнит-тестирование. Для этого создаём простой проект `HelloCatch` со следующим исходным кодом:

```c++
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int computeSum (int x, int y)
{
    return x + y;
}

int computeProduct (int x, int y)
{
    return x * y;
}

TEST_CASE("Computing sum", "[computations]")
{
    REQUIRE(computeSum(1, 2) == 3);
}

TEST_CASE("Computing product", "[computations]")
{
    REQUIRE(computeProduct(1, 2) == 3);
}
```

Здесь директива препроцессора `#define CATCH_CONFIG_MAIN` просит Catch2 создать для нас метод <code>main</code>, который сам обнаружит и выполнит соответствующие тесты. Очень удобно!

Запустив полученный EXE-файл, мы получим ошибку (надеюсь, Вы заметили, что в одном из тестов преднамеренно сделано неверное утверждение `1 * 2 == 3`?):

![catch-run1](img/catch-run1.png)

Встроенный в Catch2 тестировщик довольно функциональный. Узнать все его возможности можно, задав команду `-?`:

```
Catch v2.11.1
usage:
  HelloCatch.exe [<test name|pattern|tags> ... ] options

where options are:
  -?, -h, --help                            display usage information
  -l, --list-tests                          list all/matching test cases
  -t, --list-tags                           list all/matching tags
  -s, --success                             include successful tests in
                                            output
  -b, --break                               break into debugger on failure
  -e, --nothrow                             skip exception tests
  -i, --invisibles                          show invisibles (tabs, newlines)
  -o, --out <filename>                      output filename
  -r, --reporter <name>                     reporter to use (defaults to
                                            console)
  -n, --name <name>                         suite name
  -a, --abort                               abort at first failure
  -x, --abortx <no. failures>               abort after x failures
  -w, --warn <warning name>                 enable warnings
  -d, --durations <yes|no>                  show test durations
  -f, --input-file <filename>               load test names to run from a
                                            file
  -#, --filenames-as-tags                   adds a tag for the filename
  -c, --section <section name>              specify section to run
  -v, --verbosity <quiet|normal|high>       set output verbosity
  --list-test-names-only                    list all/matching test cases
                                            names only
  --list-reporters                          list all reporters
  --order <decl|lex|rand>                   test case order (defaults to
                                            decl)
  --rng-seed <'time'|number>                set a specific seed for random
                                            numbers
  --use-colour <yes|no>                     should output be colourised
  --libidentify                             report name and version according
                                            to libidentify standard
  --wait-for-keypress <start|exit|both>     waits for a keypress before
                                            exiting
  --benchmark-samples <samples>             number of samples to collect
                                            (default: 100)
  --benchmark-resamples <resamples>         number of resamples for the
                                            bootstrap (default: 100000)
  --benchmark-confidence-interval           confidence interval for the
  <confidence interval>                     bootstrap (between 0 and 1,
                                            default: 0.95)
  --benchmark-no-analysis                   perform only measurements; do not
                                            perform any analysis

For more detailed usage please see the project docs
```

В CLion встроена поддержка Catch2, можно указать шаблон запуска приложения-тестера:

![catch-run2](img/catch-run2.png)

Вот как выглядит тестирование в этом случае:

![catch-run3](img/catch-run3.png)

Для Visual Studio имеется расширение [Test Adapter for Catch2](https://marketplace.visualstudio.com/items?itemName=JohnnyHendriks.ext01). Оно поддерживает VS 2017 и 2019 (включая Community Edition, конечно же). "Из коробки" оно не умеет обнаруживать тесты, ему нужно подсказать, положив рядом с проектом файл конфигурации `Catch.runsettings` (имя можно выбирать произвольно, расширение должно быть `runsettings`) примерно такого содержания:

```xml
<?xml version="1.0" encoding="utf-8"?>
<RunSettings>

  <Catch2Adapter>
    <FilenameFilter>Test</FilenameFilter>
  </Catch2Adapter>

</RunSettings>
```

Мы просто указываем, что искать тесты надо в файлах, содержащих слово `Test`. При желании можно предложить любой другой алгоритм обнаружения тестов. Теперь надо подключить `runsettings` к системе юнит-тестов Visual Studio:

![catch-run4](img/catch-run4.png)

Теперь тесты прекрасно выполняются и в Visual Studio:

![catch-run5](img/catch-run5.png)

Вернёмся обратно к написанию тестов. Кроме `REQUIRE` доступно ещё множество тестирующих макросов, например, `CHECK`. Он отличается тем, что при обнаружении ошибки печатает диагностику и продолжает выполнение текущего теста, а `REQUIRE` прерывает текущий `TEST_CASE`.

Внутри теста может быть произвольное количество так называемых секций:

```c++
TEST_CASE("Computing sum", "[computations]")
{
    SECTION("Small numbers") {
        REQUIRE(computeSum(1, 2) == 3);
    }

    SECTION("Bigger numbers") {
        REQUIRE(computeSum(10000000, 2000000) == 3000000);
    }
}
```
