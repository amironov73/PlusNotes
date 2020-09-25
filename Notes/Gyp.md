### Система сборки GYP

[https://ru.wikipedia.org/wiki/GYP_(программное_обеспечение)](https://ru.wikipedia.org/wiki/GYP_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%BD%D0%BE%D0%B5_%D0%BE%D0%B1%D0%B5%D1%81%D0%BF%D0%B5%D1%87%D0%B5%D0%BD%D0%B8%D0%B5))

GYP (от англ. Generate Your Projects) — система автоматизации сборки, созданная компанией Google для генерации проектов различных IDE (таких как Visual Studio Code или Xcode). Первоначально утилита была создана для сборки браузера Chromium и родственных продуктах, например, в движке V8, Node.js и т.п. На сегодняшний день инструмент можно использовать и в других проектах. Программа распространяется на условиях лицензии BSD.

GYP представляет собой мета-сборочную систему в том смысле, что сам GYP не собирает проекты, а лишь генерирует сценарии для других систем сборки. GYP создана в помощь большим проектам, которые должны собираться на множестве платформ (например, Mac, Windows, Linux), и для которых важно, что проект может быть собран посредством IDE, популярной на каждой платформе, как будто проект является родным.

Официальный сайт: https://gyp.gsrc.io, репозиторий: https://chromium.googlesource.com/external/gyp

Как говорится, лучше один раз увидеть, чем 100 раз услышать. Допустим, у нас есть проект: консольная программа `hello`, вычисляющая нечто невероятно сложное и важное. Её исходники состоят из двух C-файлов `main.c` и `functions.c` в папке `src` и одного заголовочного файла `hello.h` в папке `include`. Вот как это всё описывается в файле `hello.gyp`:

```json
{
   'targets': [
     {
       'target_name': 'hello',
       'type': 'executable',
       'dependencies': [],
       'sources': [
         'src/functions.c',
         'src/main.c',
       ],
       'include_dirs': [
         'include',
       ],
     }
   ]
}
```

Устанавливается это дело тривиально:

```bash
sudo apt install gyp
```

Впрочем, можно просто склонировать репозиторий к себе:

```bash
git clone --depth=1 https://chromium.googlesource.com/external/gyp
```

Опции командной строки:

```
Usage: gyp_main.py [options ...] [build_file ...]

Options:
  -h, --help            show this help message and exit
  --build=CONFIGS       configuration for build after project generation
  --check               check format of gyp files
  --config-dir=CONFIG_DIR
                        The location for configuration files like
                        include.gypi.
  -d DEBUGMODE, --debug=DEBUGMODE
                        turn on a debugging mode for debugging GYP.  Supported
                        modes are "variables", "includes" and "general" or
                        "all" for all of them.
  -D VAR=VAL            sets variable VAR to value VAL
  --depth=PATH          set DEPTH gyp variable to a relative path to PATH
  -f FORMATS, --format=FORMATS
                        output formats to generate
  -G FLAG=VAL           sets generator flag FLAG to VAL
  --generator-output=DIR
                        puts generated build files under DIR
  --ignore-environment  do not read options from environment variables
  -I INCLUDE, --include=INCLUDE
                        files to include in all loaded .gyp files
  --no-circular-check   don't check for circular relationships between files
  --no-duplicate-basename-check
                        don't check for duplicate basenames
  --no-parallel         Disable multiprocessing
  -S SUFFIX, --suffix=SUFFIX
                        suffix to add to generated files
  --toplevel-dir=DIR    directory to use as the root of the source tree
  -R TARGET, --root-target=TARGET
                        include only TARGET and its deep dependencies
```

Под Windows запускаем

```bash
gyp hello.gyp --depth .
```

и получаем файл `hello.vcproj`, который моя Visual Studio без проблем открывает и собирает. Под Linux и OS X для нас генерируют `Makefile`, который без проблем собирается GNU Make.

Согласитесь, симпатичная система.
