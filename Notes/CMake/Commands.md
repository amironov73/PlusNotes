### Команды

https://cmake.org/cmake/help/v3.17/manual/cmake-commands.7.html

#### Команды скриптинга

* **break** – выход из цикла `foreach` или `while`;

* **cmake_host_system_information \(RESULT \<variable\> QUERY \<key\> …\)** – запрос информации о хосте, на котором производится сборка:

  | Key                       | Description
  |---------------------------|------------------------
  | NUMBER_OF_LOGICAL_CORES   | Number of logical cores
  | NUMBER_OF_PHYSICAL_CORES  | Number of physical cores
  | HOSTNAME                  | Hostname
  | FQDN                      | Fully qualified domain name
  | TOTAL_VIRTUAL_MEMORY      | Total virtual memory in MiB
  | AVAILABLE_VIRTUAL_MEMORY  | Available virtual memory in MiB
  | TOTAL_PHYSICAL_MEMORY     | Total physical memory in MiB
  | AVAILABLE_PHYSICAL_MEMORY | Available physical memory in MiB
  | IS_64BIT                  | One if processor is 64Bit 
  | HAS_FPU                   | One if processor has floating point unit
  | HAS_MMX                   | One if processor supports MMX instructions
  | HAS_MMX_PLUS              | One if processor supports Ext. MMX instructions
  | HAS_SSE                   | One if processor supports SSE instructions
  | HAS_SSE2                  | One if processor supports SSE2 instructions
  | HAS_SSE_FP                | One if processor supports SSE FP instructions
  | HAS_SSE_MMX               | One if processor supports SSE MMX instructions
  | HAS_AMD_3DNOW             | One if processor supports 3DNow instructions
  | HAS_AMD_3DNOW_PLUS        | One if processor supports 3DNow+ instructions
  | HAS_IA64                  | One if IA64 processor emulating x86
  | HAS_SERIAL_NUMBER         | One if processor has serial number
  | PROCESSOR_SERIAL_NUMBER   | Processor serial number
  | PROCESSOR_NAME            | Human readable processor name
  | PROCESSOR_DESCRIPTION     | Human readable full processor description
  | OS_NAME                   | See CMAKE_HOST_SYSTEM_NAME
  | OS_RELEASE                | The OS sub-type e.g. on Windows Professional
  | OS_VERSION                | The OS build ID
  | OS_PLATFORM               | See CMAKE_HOST_SYSTEM_PROCESSOR

  ```cmake
  cmake_host_system_information(RESULT vmem QUERY AVAILABLE_VIRTUAL_MEMORY)
  message("Virtual memory = " ${vmem} " MB")
  ```
 
* **cmake_minimum_required \(VERSION \<min\>\[…\<max\>\] \[FATAL_ERROR\]\)** – указание необходимой версии CMake;

* **cmake_parse_arguments \(\<prefix\> \<options\> \<one_value_keywords\> \<multi_value_keywords\> \<args\> …\)** – команда для использования в макросах или функциях;

* **cmake_policy** – управление политиками;

* **configure_file \(\<input\> \<output\>\[COPYONLY\] \[ESCAPE_QUOTES\] \[@ONLY\] \[NEWLINE_STYLE \[UNIX|DOS|WIN32|LF|CRLF\] \]\)** – копирование файла с расширением переменных;

* **continue** – пропуск одной итерации в цикле `foreach` или `while`;

* **else** – ветка ИНАЧЕ в команде `if`;

* **elseif** – ветка ИНАЧЕ-ЕСЛИ в команде `if`;

* **endforeach** – закрывающая команда для `foreach`;

* **endfunction** – закрывающая команда для `function`;

* **endif** – закрывающая команда для `if`;

* **endmacro** – закрывающая команда для `macro`;

* **endwhile** – закрывающая команда для `while`;

* **execute_process** – запуск одного или более подпроцесса;

* **file** – манипуляции с файлами:

  ```
  Reading
    file(READ <filename> <out-var> [...])
    file(STRINGS <filename> <out-var> [...])
    file(<HASH> <filename> <out-var>)
    file(TIMESTAMP <filename> <out-var> [...])
    file(GET_RUNTIME_DEPENDENCIES [...])
  
  Writing
    file({WRITE | APPEND} <filename> <content>...)
    file({TOUCH | TOUCH_NOCREATE} [<file>...])
    file(GENERATE OUTPUT <output-file> [...])
  
  Filesystem
    file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
    file(RENAME <oldname> <newname>)
    file({REMOVE | REMOVE_RECURSE } [<files>...])
    file(MAKE_DIRECTORY [<dir>...])
    file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
    file(SIZE <filename> <out-var>)
    file(READ_SYMLINK <linkname> <out-var>)
    file(CREATE_LINK <original> <linkname> [...])
  
  Path Conversion
    file(RELATIVE_PATH <out-var> <directory> <file>)
    file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)
  
  Transfer
    file(DOWNLOAD <url> <file> [...])
    file(UPLOAD <file> <url> [...])
  
  Locking
    file(LOCK <path> [...])
  ```
  
  * **file(READ \<filename\> \<variable\> \[OFFSET \<offset\>\] \[LIMIT \<max-in\>\] \[HEX\])** – считывание всего файла в переменную как одной длинной строки.
  
  * **file(STRINGS \<filename\> \<variable\> \[\<options\>...\])** – считывание всего файла в переменную как массива строк. Символы `\r` игнорируются. Опции:
  
    * **LENGTH_MAXIMUM \<max-len\>** – строки не больше указанной длины;
    * **LENGTH_MINIMUM \<min-len\>** – строки не меньше указанной длины;
    * **LIMIT_COUNT \<max-num\>** – ограничение количества различных извлекаемых строк;
    * **LIMIT_INPUT \<max-in\>** – ограничение количества считываемых из файла байт;
    * **LIMIT_OUTPUT \<max-out\>** – ограничение общего размера переменной, в которую помещаются строки;
    * **NEWLINE_CONSUME** – трактовать `\n` как часть строки, не удалять её;
    * **NO_HEX_CONVERSION** – если эта опция не задана, файлы Intel Hex и Motorola S-record автоматически конвертируются в двоичные;
    * **REGEX \<regex\>** – рассматривать только строки, удовлетворяющие регулярному выражению;
    * **ENCODING \<encoding-type\>** – считывать в указанной кодировке. Поддерживаются: UTF-8, UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE.
    
  * **file(\<HASH\> \<filename\> \<variable\>)** – рассчитать указанный хеш содержимого файла;
  
  * **file(TIMESTAMP \<filename\> \<variable\> \[\<format\>\] \[UTC\])** – время модификации файла;
  
  * **file(GET_RUNTIME_DEPENDENCIES)** – список файлов, от которых зависят указанные файлы:
  
      ```
      file(GET_RUNTIME_DEPENDENCIES
        [RESOLVED_DEPENDENCIES_VAR <deps_var>]
        [UNRESOLVED_DEPENDENCIES_VAR <unresolved_deps_var>]
        [CONFLICTING_DEPENDENCIES_PREFIX <conflicting_deps_prefix>]
        [EXECUTABLES [<executable_files>...]]
        [LIBRARIES [<library_files>...]]
        [MODULES [<module_files>...]]
        [DIRECTORIES [<directories>...]]
        [BUNDLE_EXECUTABLE <bundle_executable_file>]
        [PRE_INCLUDE_REGEXES [<regexes>...]]
        [PRE_EXCLUDE_REGEXES [<regexes>...]]
        [POST_INCLUDE_REGEXES [<regexes>...]]
        [POST_EXCLUDE_REGEXES [<regexes>...]]
        )
      ```
  
    * **RESOLVED_DEPENDENCIES_VAR \<deps_var\>** –
    * **UNRESOLVED_DEPENDENCIES_VAR \<unresolved_deps_var\>** –
    * **CONFLICTING_DEPENDENCIES_PREFIX \<conflicting_deps_prefix\>** –
    * **EXECUTABLES \<executable_files\>** –
    * **LIBRARIES \<library_files\>** –
    * **MODULES \<module_files\>** –
    * **DIRECTORIES \<directories\>** –
    * **BUNDLE_EXECUTABLE \<bundle_executable_file\>** –
    * **PRE_INCLUDE_REGEXES \<regexes\>** –
    * **PRE_EXCLUDE_REGEXES \<regexes\>** –
    * **POST_INCLUDE_REGEXES \<regexes\>** –
    * **POST_EXCLUDE_REGEXES \<regexes\>** –
    
  * **file(WRITE \<filename> \<content>...)** – запись в файл. Файл перезаписывается полностью;
  
  * **file(APPEND \<filename> \<content>...)** – запись в файл. Содержимое файла дополняется;
  
  * **file(TOUCH \[\<files\>...\])** – установка времени модификации файлов. Если файла нет, он создаётся;
  
  * **file(TOUCH_NOCREATE \[\<files\>...\])** – установка времени модификации файлов. Если файла нет, он НЕ создаётся;
  
  * **file(GENERATE OUTPUT)** – генерация выходного файла текущим генераторомL
   
    ```
    file(GENERATE OUTPUT output-file
         <INPUT input-file\|CONTENT content>
         [CONDITION expression])
    ```
  
    * **CONDITION \<condition\>** — контент генерируется только при выполнении условия;
    * **CONTENT \<content\>** – входной контент;
    * **INPUT \<input-file\>** – использовать содержимое файла в качестве входного контента;
    * **OUTPUT \<output-file\>** – записать результат в файл;
    
  * **file(GLOB)** и **file(GLOB_RECURSE)** – получение списка файлов по заданному шаблону:
  
    ```
    file(GLOB <variable>
         [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
         [<globbing-expressions>...])
    file(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS]
         [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
         [<globbing-expressions>...])
    ```
    
  * **file(RENAME \<oldname\> \<newname\>)** – переименование файлов;
  
  * **file(REMOVE \[\<files\>...\])** – удаление перечисленных файлов;
  
  * **file(REMOVE_RECURSE \[\<files\>...\])** – рекурсивное удаление перечисленных файлов;
  
  * **file(MAKE_DIRECTORY \[\<directories\>...\])** – создание директорий;
  
  * **file(COPY)** – копирование файлов:
  
    ```
    file(<COPY|INSTALL> <files>... DESTINATION <dir>
         [FILE_PERMISSIONS <permissions>...]
         [DIRECTORY_PERMISSIONS <permissions>...]
         [NO_SOURCE_PERMISSIONS] [USE_SOURCE_PERMISSIONS]
         [FOLLOW_SYMLINK_CHAIN]
         [FILES_MATCHING]
         [[PATTERN <pattern> | REGEX <regex>]
          [EXCLUDE] [PERMISSIONS <permissions>...]] [...])
    ```
    
  * **file(SIZE \<filename\> \<variable\>)** – определение размера файла;
  
  * **file(READ_SYMLINK \<linkname\> \<variable\>)** – чтение символической ссылки;
  
  * **file(CREATE_LINK \<original\> \<linkname\> \[RESULT \<result\>] \[COPY_ON_ERROR\] \[SYMBOLIC\])** – создание ссылки;
  
  * **file(RELATIVE_PATH \<variable\> \<directory\> \<file\>)** – преобразование пути в относительный;
  
  * **file(TO_CMAKE_PATH \<path\> \<variable\>)** – конвертирует обратные слэши в прямые, понятные CMake;
  
  * **file(TO_NATIVE_PATH \<path\> \<variable\>)** – конвертирует CMake-style пути в нативные, при необходимости превращая прямые слэши в обратные;
  
  * **file(DOWNLOAD) и file(UPLOAD)** – скачивание и загрузка файлов:
  
    ```
    file(DOWNLOAD <url> <file> [<options>...])
    file(UPLOAD   <file> <url> [<options>...])
    ```
    
    Опции:
    
    * **INACTIVITY_TIMEOUT \<seconds\>** – период неактивности;
    * **LOG \<variable\>** – логирование;
    * **SHOW_PROGRESS** – отображать индиактор прогресса;
    * **STATUS \<variable\>** – сохранение HTTP-статуса;
    * **TIMEOUT \<seconds\>** – общий таймаут операции;
    * **USERPWD \<username\>:\<password\>** – задание логина-пароля;
    * **HTTPHEADER \<HTTP-header\>** – задание HTTP-заголовка;
    * **NETRC \<level\>** – уровень поддержки `.netrc`;
      * **IGNORED** – игнорируется (по умолчанию);
      * **OPTIONAL** – опционально;
      * **REQUIRED** –  требуется;
    * **NETRC_FILE \<file\>** – задание `.netrc` файла;
    * **EXPECTED_HASH ALGO=\<value\>** – ожидаемый хеш;
    * **EXPECTED_MD5 \<value\>** – ожидаемый хеш;
    * **TLS_VERIFY \<ON|OFF\>** – включение/отключение проверки сертификатов;
    * **TLS_CAINFO \<file\>** – задание сертификата;
    
  * **file(LOCK)** – блокирование файлов:
  
    ```
    file(LOCK <path> [DIRECTORY] [RELEASE]
         [GUARD <FUNCTION|FILE|PROCESS>]
         [RESULT_VARIABLE <variable>]
         [TIMEOUT <seconds>])
    ```
    
    Обратите внимание, что другие процессы не обязаны обращать внимание на блокировки, установленные CMake.

* **find_file** – поиск файла вообще \(получение полного пути к файлу, про который не известно точно, где он расположен\);

* **find_library** – поиск библиотеки;

* **find_package** – поиск пакета;

* **find_path** – поиск папки, содержащей указанный файл;

* **find_program** – поиск программы;

* **foreach** – цикл ДЛЯ:

  ```cmake
  foreach(<loop_var> <items>)
    commands()
  endforeach()
  ```

* **function** – определение функции:

  ```cmake
  function(<name> [<arg1> ...])
    commands()
  endfunction()
  ```

* **get_cmake_property** –

* **get_directory_property** –

* **get_filename_component** –

* **get_property** –

* **if** – условный оператор;

* **include \(\<file|module\> \[OPTIONAL\] \[RESULT_VARIABLE \<var\>\] \[NO_POLICY_SCOPE\]\)** – включение скрипта из указанного файла. Если указано `OPTIONAL`, то при отсутствии указанного файла ошибки не будет;

* **include_guard** –

* **list** –

* **macro** –

* **mark_as_advanced** –

* **math** –

* **message** –

* **option** –

* **return** –

* **separate_arguments** –

* **set** –

* **set_directory_properties** –

* **set_property** –

* **site_name** –

* **string** – манипуляции со строками:

  ```
  Search and Replace
    string(FIND <string> <substring> <out-var> [...])
    string(REPLACE <match-string> <replace-string> <out-var> <input>...)
  
  Regular Expressions
    string(REGEX MATCH <match-regex> <out-var> <input>...)
    string(REGEX MATCHALL <match-regex> <out-var> <input>...)
    string(REGEX REPLACE <match-regex> <replace-expr> <out-var> <input>...)
  
  Manipulation
    string(APPEND <string-var> [<input>...])
    string(PREPEND <string-var> [<input>...])
    string(CONCAT <out-var> [<input>...])
    string(JOIN <glue> <out-var> [<input>...])
    string(TOLOWER <string> <out-var>)
    string(TOUPPER <string> <out-var>)
    string(LENGTH <string> <out-var>)
    string(SUBSTRING <string> <begin> <length> <out-var>)
    string(STRIP <string> <out-var>)
    string(GENEX_STRIP <string> <out-var>)
    string(REPEAT <string> <count> <out-var>)
  
  Comparison
    string(COMPARE <op> <string1> <string2> <out-var>)
  
  Hashing
    string(<HASH> <out-var> <input>)
  
  Generation
    string(ASCII <number>... <out-var>)
    string(CONFIGURE <string> <out-var> [...])
    string(MAKE_C_IDENTIFIER <string> <out-var>)
    string(RANDOM [<option>...] <out-var>)
    string(TIMESTAMP <out-var> [<format string>] [UTC])
    string(UUID <out-var> ...)
  ```

  * **string(FIND \<string\> \<substring\> \<output_variable\> \[REVERSE\])** –
  
  * **string(REPLACE \<match_string\> \<replace_string\> \<output_variable\> \<input\> \[\<input\>...\])** –
  
  * **string(REGEX MATCH \<regular_expression\> \<output_variable\> \<input\> \[\<input\>...\])** –
  
  * **string(REGEX MATCHALL \<regular_expression\> \<output_variable\> \<input\> \[\<input\>...\])** –
  
  * **string(REGEX REPLACE \<regular_expression\> \<replacement_expression\> \<output_variable\> \<input\> \[\<input\>...\])** –
  
  * **string(APPEND \<string_variable\> \[\<input\>...\])** –
  
  * **string(PREPEND \<string_variable\> \[\<input\>...\])** –
  
  * **string(CONCAT \<output_variable\> \[\<input\>...\])** –
  
  * **string(JOIN \<glue\> \<output_variable\> \[\<input>...\])** –
  
  * **string(TOLOWER \<string\> \<output_variable\>)** –
  
  * **string(TOUPPER \<string\> \<output_variable\>)** –
  
  * **string(LENGTH \<string\> \<output_variable\>)** –
  
  * **string(SUBSTRING \<string\> \<begin\> \<length\> \<output_variable\>)** –
  
  * **string(STRIP \<string\> \<output_variable\>)** –
  
  * **string(GENEX_STRIP \<string\> \<output_variable\>)** –
  
  * **string(REPEAT \<string\> \<count\> \<output_variable\>)** –
  
  * **string(COMPARE)** –
  
    ```
    string(COMPARE LESS <string1> <string2> <output_variable>)
    string(COMPARE GREATER <string1> <string2> <output_variable>)
    string(COMPARE EQUAL <string1> <string2> <output_variable>)
    string(COMPARE NOTEQUAL <string1> <string2> <output_variable>)
    string(COMPARE LESS_EQUAL <string1> <string2> <output_variable>)
    string(COMPARE GREATER_EQUAL <string1> <string2> <output_variable>)
    ```
    
  * **string(\<HASH\> \<output_variable\> \<input\>)** —
  
  * **string(ASCII \<number\> \[\<number\> ...\] \<output_variable\>)** –
  
  * **string(CONFIGURE \<string\> \<output_variable\> \[\@ONLY\] \[ESCAPE_QUOTES\])** –
  
  * **string(MAKE_C_IDENTIFIER \<string\> \<output_variable\>)** –
  
  * **string(RANDOM \[LENGTH \<length\>\] \[ALPHABET \<alphabet\>\] \[RANDOM_SEED \<seed\>\] \<output_variable\>)** –
  
  * **string(TIMESTAMP \<output_variable\> \[\<format_string\>\] \[UTC\])** –
  
  * **string(UUID \<output_variable\> NAMESPACE <\namespace\> NAME \<name\> TYPE \<MD5|SHA1\> \[UPPER\])** –

* **unset \(\<variable\> \[CACHE | PARENT_SCOPE\]\)** – удаление обычной переменной CMake. Для удаления переменной окружения `unset(ENV{<variable>})`;

* **variable_watch \(\<variable\> \[\<command\>\]\)** – отслеживать изменения переменной. Когда указанная переменная поменяет значение, будет выведено соответствующее сообщение, либо выполнена указанная команда;

* **while** – цикл ПОКА:

  ```cmake
  while(<condition>)
    commands()
  endwhile()
  ```

#### Команды проекта

* **add_compile_definitions** –

* **add_compile_options** –

* **add_custom_command** –

* **add_custom_target** –

* **add_definitions** –

* **add_dependencies** –

* **add_executable** –

* **add_library** –

* **add_link_options** –

* **add_subdirectory** –

* **add_test** –

* **aux_source_directory** –

* **build_command** –

* **create_test_sourcelist** –

* **define_property** –

* **enable_language** –

* **enable_testing** –

* **export** –

* **fltk_wrap_ui** –

* **get_source_file_property** –

* **get_target_property** –

* **get_test_property** –

* **include_directories** –

* **include_external_msproject** –

* **include_regular_expression** –

* **install** –

* **link_directories** –

* **link_libraries** –

* **load_cache** –

* **project** – устанавливает имя проекта, сохраняя его в переменной `PROJECT_NAME`. Заодно инициализируются переменные `PROJECT_SOURCE_DIR`, `<PROJECT-NAME>_SOURCE_DIR`, `PROJECT_BINARY_DIR` и `<PROJECT-NAME>_BINARY_DIR`.

    ```
    project(<PROJECT-NAME> [<language-name>...])
    project(<PROJECT-NAME>
            [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
            [DESCRIPTION <project-description-string>]
            [HOMEPAGE_URL <url-string>]
            [LANGUAGES <language-name>...])
    ```

    * **VERSION \<version\>** – задаёт версию проекта в виде `<major>[.<minor>[.<patch>[.<tweak>]]]`. Заодно инициализируются переменные `PROJECT_VERSION`, `PROJECT_VERSION_MAJOR`, `PROJECT_VERSION_MINOR`, `PROJECT_VERSION_PATCH`, `PROJECT_VERSION_TWEAK`, `<PROJECT-NAME>_VERSION`, `<PROJECT-NAME>_VERSION_MAJOR`, `<PROJECT-NAME>_VERSION_MINOR`, `<PROJECT-NAME>_VERSION_PATCH` и `<PROJECT-NAME>_VERSION_TWEAK`. Для топового `CMakeLists.txt` также инициализируется переменная `CMAKE_PROJECT_VERSION` (со всеми остановками).
    
    * **DESCRIPTION \<project-description-string\>** – опциональное описание проекта. Заодно инициализируются переменные `PROJECT_DESCRIPTION` и `<PROJECT-NAME>_DESCRIPTION`. Для топового `CMakeLists.txt` инициализируется переменная `CMAKE_PROJECT_DESCRIPTION`. 
    
    * **HOMEPAGE_URL \<url-string\>** – опциональная домашняя страница проекта.
    
    * **LANGUAGES \<language-name\>...** – опциональное перечисление языков, используемых в проекте.

* **remove_definitions** –

* **set_source_files_properties** –

* **set_target_properties** –

* **set_tests_properties** –

* **source_group** –

* **target_compile_definitions** –

* **target_compile_features** –

* **target_compile_options** –

* **target_include_directories** –

* **target_link_directories** –

* **target_link_libraries** –

* **target_link_options** –

* **target_precompile_headers** –

* **target_sources** –

* **try_compile** –

* **try_run** –

#### CTest

* **ctest_build** –

* **ctest_configure** –

* **ctest_coverage** –

* **ctest_empty_binary_directory** –

* **ctest_memcheck** –

* **ctest_read_custom_files** –

* **ctest_run_script** —

* **ctest_sleep** –

* **ctest_start** –

* **ctest_submit** –

* **ctest_test** –

* **ctest_update** –

* **ctest_upload** –
