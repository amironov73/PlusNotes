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

* **file** – манипуляции с файлами;

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

* **string** –

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

* **project** –

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