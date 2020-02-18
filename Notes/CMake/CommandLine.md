### Командная строка

#### Генерация проекта

```
cmake [<options>] <path-to-source>
cmake [<options>] <path-to-existing-build>
cmake [<options>] -S <path-to-source> -B <path-to-build>
```

Опции

* **-S \<path-to-source\>** – указание директории, в которой находится `CMakeLists.txt`.

* **-B \<path-to-build\>** – указание папки, в которой будет производиться. Если папка не существует, CMake создаст её.

* **-C \<initial-cache\>** – задание файла с кэшом `CMakeCache.txt`.

* **-D \<var\>:\<type\>\=<value>, -D \<var \>\=\<value\>** — задание переменной, помещение её в кэш (т. е. при следующем запуске эту переменную можно не указывать, она будет взята из кеша). Можно без пробела: `-D<var>:<type>=<value>`.

* **-U \<globbing_expr\>** – удаление ранее заданной переменной из кеша. Чтобы удалить все: `-U *`.

* **-G \<generator-name\>** – указание генератора. См. [Генераторы](Generators.md)ю

* **-T \<toolset-spec\>** — указание тулсета.

* **-A \<platform-name\>** — указание платформы (если поддерживается генератором). Для Visual Studio: `Win32`, `x64`, `ARM`, `ARM64`. Пример: `cmake -G "Visual Studio 16 2019" -A x64`.

* **-Wno-dev** — подавление девелоперских предупреждений.

* **-Wdev** — включение девелоперских предупреждений.

Стандартная последовательность для старых версий CMake:

```
mkdir build ; cd build
cmake ..
```

#### Сборка проекта

```
cmake --build <dir> [<options>] [-- <build-tool-options>]
```

* **--build \<dir\>** – сборка согласно ранее сгенерированным файлам.

* **--parallel \[\<jobs\>\], -j \[\<jobs\>\]** – параллельная сборка в несколько потоков.

* **--target \<tgt\>..., -t \<tgt\>...** – сборка указанной цели.

* **--config \<cfg\>** – сборка указанной конфигурации (например, `Release`).

* **--clean-first** — сначала выполняется цель `clean`, затем сборка проекта.

* **--verbose, -v** – подробный вывод.

* **--** – последующие аргументы будут переданы системе сборки.

#### Инсталляция проекта

```
cmake --install <dir> [<options>]
```

* **--install \<dir\>** – указание папки с билд-файлами.

* **--config \<cfg\>** – выбор конфигурации для инсталляции.

* **--component \<comp\>** – выбор компонента для инсталляции.

* **--prefix \<prefix\>** – переопределение префикса для инсталляции.

* **--strip** — удаление отладочной информации перед инсталляцией.

* **-v, --verbose** — подробный вывод.

Для старых версий CMake:

```
cmake --build <dir> --target install
```

#### Открытие сгенерированного проекта

```
cmake --open <dir>
```

Запускает, например, Visual Studio со сгенерированным проектом/солюшеном. Поддерживается не для всех генераторов.

#### Запуск скрипта

```
cmake [{-D <var>=<value>}...] -P <cmake-script-file>
```

#### Выполнение разнообразных действий

```
cmake -E <command> [<options>]
```

* **capabilities** – перечисление доступных возможностей CMake в формате JSON. Выглядит это так:

```json
{
  "fileApi": {
    "requests": [
      {
        "kind": "codemodel",
        "version": [
          {
            "major": 2,
            "minor": 0
          }
        ]
      },
      {
        "kind": "cache",
        "version": [
          {
            "major": 2,
            "minor": 0
          }
        ]
      },
      {
        "kind": "cmakeFiles",
        "version": [
          {
            "major": 1,
            "minor": 0
          }
        ]
      }
    ]
  },
  "generators": [
    {
      "extraGenerators": [],
      "name": "Visual Studio 14 2015 ARM",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 16 2019",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 15 2017 Win64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 15 2017",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 15 2017 ARM",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 14 2015 Win64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 12 2013",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 12 2013 Win64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 14 2015",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [
        "CodeBlocks",
        "CodeLite",
        "Sublime Text 2",
        "Kate",
        "Eclipse CDT4"
      ],
      "name": "MinGW Makefiles",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 12 2013 ARM",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 11 2012",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 11 2012 ARM",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [
        "CodeBlocks",
        "CodeLite",
        "Sublime Text 2",
        "Kate",
        "Eclipse CDT4"
      ],
      "name": "Unix Makefiles",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 11 2012 Win64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 10 2010 Win64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 10 2010",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 10 2010 IA64",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 9 2008",
      "platformSupport": true,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 9 2008 Win64",
      "platformSupport": true,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [
        "CodeBlocks"
      ],
      "name": "NMake Makefiles JOM",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Visual Studio 9 2008 IA64",
      "platformSupport": true,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "MSYS Makefiles",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Borland Makefiles",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [
        "CodeBlocks",
        "CodeLite",
        "Sublime Text 2",
        "Kate",
        "Eclipse CDT4"
      ],
      "name": "NMake Makefiles",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Green Hills MULTI",
      "platformSupport": true,
      "toolsetSupport": true
    },
    {
      "extraGenerators": [
        "CodeBlocks",
        "CodeLite",
        "Sublime Text 2",
        "Kate",
        "Eclipse CDT4"
      ],
      "name": "Ninja",
      "platformSupport": false,
      "toolsetSupport": false
    },
    {
      "extraGenerators": [],
      "name": "Watcom WMake",
      "platformSupport": false,
      "toolsetSupport": false
    }
  ],
  "serverMode": true,
  "version": {
    "isDirty": false,
    "major": 3,
    "minor": 16,
    "patch": 0,
    "string": "3.16.0",
    "suffix": ""
  }
}
```

* **chdir \<dir\> \<cmd\> \[\<arg\>...\]** – смена текущей директории.

* **compare_files \[--ignore-eol\] \<file1\> \<file2\>** – сравнение двух файлов. Возвращает `0`, если файлы совпадают.

* **copy \<file\>... \<destination\>** – копирование файлов.

* **copy_directory \<dir\>... \<destination\>** – копирование папок.

* **copy_if_different \<file\>... \<destination\>** – копирование файла только в том случае, если он изменялся.

* **create_symlink \<old\> \<new\>** – создание символической ссылки.

* **echo \[\<string\>...\]** – вывод текста в консоль.

* **echo_append \[\<string\>...\]** – аналогично `echo`, но без перевода строки в конце.

* **env \[--unset=NAME\]... \[NAME=VALUE\]... COMMAND \[ARG\]...** – манипуляции с переменными окружения.

* **environment** – вывод переменных окружения.

* **false** – ничего не делает, просто выходит с кодом `1`.

* **make_directory \<dir\>...** – создание папок.

* **md5sum \<file\>...** – создание файла с контрольными суммами в формате:

  ```
  351abe79cd3800b38cdfb25d45015a15  file1.txt
  052f86c15bbde68af55c7f7b340ab639  file2.txt
  ```

* **sha1sum \<file\>...** – создание файла с контрольными суммами в формате:

  ```
  4bb7932a29e6f73c97bb9272f2bdc393122f86e0  file1.txt
  1df4c8f318665f9a5f2ed38f55adadb7ef9f559c  file2.txt
  ```
  
* **sha224sum \<file\>...** – создание файла с контрольными суммами в формате:  
  
  ```
  b9b9346bc8437bbda630b0b7ddfc5ea9ca157546dbbf4c613192f930  file1.txt
  6dfbe55f4d2edc5fe5c9197bca51ceaaf824e48eba0cc453088aee24  file2.txt
  ```
  
* **sha256sum \<file\>...** – создание файла с контрольными суммами в формате:  
  
  ```
  76713b23615d31680afeb0e9efe94d47d3d4229191198bb46d7485f9cb191acc  file1.txt
  15b682ead6c12dedb1baf91231e1e89cfc7974b3787c1e2e01b986bffadae0ea  file2.txt
  ```
  
* **sha384sum \<file\>...** – создание файла с контрольными суммами в формате:

  ```
  acc049fedc091a22f5f2ce39a43b9057fd93c910e9afd76a6411a28a8f2b8a12c73d7129e292f94fc0329c309df49434  file1.txt
  668ddeb108710d271ee21c0f3acbd6a7517e2b78f9181c6a2ff3b8943af92b0195dcb7cce48aa3e17893173c0a39e23d  file2.txt
  ```  
  
* **sha512sum \<file\>...** – создание файла с контрольными суммами в формате:

  ```
  2a78d7a6c5328cfb1467c63beac8ff21794213901eaadafd48e7800289afbc08e5fb3e86aa31116c945ee3d7bf2a6194489ec6101051083d1108defc8e1dba89  file1.txt
  7a0b54896fe5e70cca6dd643ad6f672614b189bf26f8153061c4d219474b05dad08c4e729af9f4b009f1a1a280cb625454bf587c690f4617c27e3aebdf3b7a2d  file2.txt
  ```
  
* **remove [-f] \<file\>...** – удаление файлов. Начиная с версии 3.17 лучше использовать `rm`.

* **remove_directory \<dir\>...** – удаление папок. Начиная с версии 3.17 лучше использовать `rm`.

* **rename \<oldname\> \<newname\>** – переименование файлов.

* **rm \[-rRf\] \<file\> \<dir\>...** – удаление файлов и папок.

* **server** – запускает CMake-сервер.

* **sleep \<number\>...** – засыпание на указанное количество секунд.

* **tar \[cxt\]\[vf\]\[zjJ\] file.tar \[<options>\] \[--\] \[<pathname>...\]** – создание или извлечение tar-архива.

* **time \<command\> \[\<args>...\]** – измерение времени исполнения команды.

* **touch \<file\>...** – создание файла, если он отсутствует. Если файл существует, его время модификации меняется на текущее.

* **touch_nocreate \<file\>...** – если файл отсутствует, ничего не происходит. Если файл существует, его время модификации меняется на текущее.

* **true** – ничего не делает, просто возвращает 0.   
  
Специфично для Windows:

* **delete_regv \<key\>** – удаление ключа реестра.

* **env_vs8_wince \<sdkname\>** – показывает batch-файл для Windows CE SDK installed в VS2005.

* **env_vs9_wince \<sdkname\>** – показывает batch-файл для Windows CE SDK installed в VS2008.
  
* **write_regv \<key\> \<value\>** – запись реестра.  
  

#### Запуск поиска пакета

```
cmake --find-package [<options>]
```

#### Вывод справки

```
cmake --help[-<topic>]
```

