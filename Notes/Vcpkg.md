### Пакетный менеджер vcpkg

В программировании на C/C++ традиционной головной болью для разработчика является подключение внешних библиотек, таких как `ziplib`, `opencv` и т. д. Не то, чтобы это была rocket science, но повторять каждый раз рутинные телодвижения, рискуя пропустить одно из них — это не то, чем должен заниматься программист. Суть программирования заключается как раз в автоматизации рутины. И Microsoft автоматизировала эту рутину, создав пакетный менеджер vcpkg.

Документация: https://vcpkg.readthedocs.io/en/latest/ и ещё одна: https://docs.microsoft.com/en-us/cpp/vcpkg, обучающий ролик: https://www.youtube.com/watch?v=y41WFKbQFTw. На данный момент в экосистеме vcpkg 849 портов (специальным образом подготовленных библиотек). На билд-серверах AppVeyor vcpkg уже установлен, это радует!

Менеджер устанавливается на машину разработчика путём скачивания исходников с GitHub с последующей компиляцией:

```
> mkdir vcpkg
> cd vcpkg
> git clone https://github.com/Microsoft/vcpkg .
> bootstrap-vcpkg.bat
```

Для vcpkg под Windows необходима любая редакция Visual Studio 2015/2017 (Community подходит) с установленным тулсетом C++ (каким конкретно, зависит от решаемых задач). Если компиляция завершится успешно (а я надеюсь, так и случится), то в корне созданной папки появится файл vcpkg.exe размером 922 Кб.

vcpkg поддерживает следующие команды и опции:

```
Commands:
  vcpkg search [pat]              Search for packages available to be built
  vcpkg install <pkg>...          Install a package
  vcpkg remove <pkg>...           Uninstall a package
  vcpkg remove --outdated         Uninstall all out-of-date packages
  vcpkg list                      List installed packages
  vcpkg update                    Display list of packages for updating
  vcpkg upgrade                   Rebuild all outdated packages
  vcpkg hash <file> [alg]         Hash a file by specific algorithm, default SHA512
  vcpkg help topics               Display the list of help topics
  vcpkg help <topic>              Display help for a specific topic
 
  vcpkg integrate install         Make installed packages available user-wide. Requires admin privileges on first use
  vcpkg integrate remove          Remove user-wide integration
  vcpkg integrate project         Generate a referencing nuget package for individual VS project use
  vcpkg integrate powershell      Enable PowerShell Tab-Completion
 
  vcpkg export <pkg>... [opt]...  Exports a package
  vcpkg edit <pkg>                Open up a port for editing (uses %EDITOR%, default 'code')
  vcpkg import <pkg>              Import a pre-built library
  vcpkg create <pkg> <url>
             [archivename]        Create a new package
  vcpkg owns <pat>                Search for files in installed packages
  vcpkg env                       Creates a clean shell environment for development or compiling.
  vcpkg version                   Display version information
  vcpkg contact                   Display contact information to send feedback
 
Options:
  --triplet <t>                   Specify the target architecture triplet.
                                  (default: %VCPKG_DEFAULT_TRIPLET%, see 'vcpkg help triplet')
 
  --vcpkg-root <path>             Specify the vcpkg root directory
                                  (default: %VCPKG_ROOT%)
 
  @response_file                  Specify a response file to provide additional parameters
 
For more help (including examples) see the accompanying README.md.
```

Попробуем найти какую-нибудь библиотечку, умеющую работать с форматом zip:

```
> vcpkg search zip
 
bzip2                1.0.6-3          High-quality data compressor.
folly[bzip2]                          Support bzip2 for compression
laszip               3.2.2-1          LASzip - free and lossless LiDAR compression
libarchive[bzip2]                     BZip2 support
libzip               rel-1-5-1-vcpkg1 A library for reading, creating, and modifying zip archives.
minizip              1.2.11-3         Zip compression library
protobuf[zlib]                        ZLib based features like Gzip streams
szip                 2.1.1-1          Szip compression software, providing lossless compression of scientific data
zziplib              0.13.69          library providing read access on ZIP-archives
 
If your library is not listed, please open an issue at and/or consider making a pull request:
    https://github.com/Microsoft/vcpkg/issues
```

Допустим, мы выбрали библиотеку bzip2:

```
> vcpkg install bzip2
                                                                                                           
The following packages will be built and installed:                                                                                      
    bzip2[core]:x86-windows                                                                                                              
Starting package 1/1: bzip2:x86-windows                                                                                                  
Building package bzip2[core]:x86-windows...                                                                                              
A suitable version of cmake was not found (required v3.12.4). Downloading portable cmake v3.12.4... 
-- Downloading https://github.com/past-due/bzip2-mirror/releases/download/v1.0.6/bzip2-1.0.6.tar.gz...
-- Extracting source downloads/bzip2-1.0.6.tar.gz
-- Applying patch fix-import-export-macros.patch
-- Using source at buildtrees/bzip2/src/1.0.6-8d81d2ad2b
-- Configuring x86-windows
-- Building x86-windows-dbg
-- Building x86-windows-rel
-- Performing CMake integration test
-- Performing post-build validation
-- Performing post-build validation done
Building package bzip2[core]:x86-windows... done
Installing package bzip2[core]:x86-windows...
Installing package bzip2[core]:x86-windows... done
Elapsed time for package bzip2:x86-windows: 3.868 min
 
Total elapsed time: 3.868 min
 
The package bzip2 is compatible with built-in CMake targets:
 
    find_package(BZip2 REQUIRED)
    target_link_libraries(main PRIVATE BZip2::BZip2)     
```
                          
Убедимся, что библиотека теперь доступна:

```
> vcpkg list
bzip2:x86-windows              1.0.6-3    High-quality data compressor.
```

И, наконец, включим интеграцию vcpkg (работает для всех новых проектов текущего пользователя):

```
> vcpkg integrate install
Applied user-wide integration for this vcpkg root.
 
All MSBuild C++ projects can now #include any installed libraries.
Linking will be handled automatically.
Installing new libraries will make them instantly available.
 
CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Если интеграция больше не нужна, её можно удалить командой

```
> vcpkg integrate remove
```

Можно ограничиться интеграцией на уровне конкретного проекта:

```
> vcpkg integrate project
Created nupkg: D:\vcpkg\scripts\buildsystems\vcpkg.D.vcpkg.1.0.0.nupkg
 
With a project open, go to Tools->NuGet Package Manager->Package Manager Console and paste:
    Install-Package vcpkg.D.vcpkg -Source "D:\vcpkg\scripts\buildsystems"
```

Структура папок vcpkg:

* **buildtrees** — содержит подпапки с исходниками всех собранных библиотек;
* **docs** — документация и примеры;
* **downloads** — кэшированные копии загруженных утилит и исходников. vcpkg сначала ищет в данной папке, и только если не найдёт здесь, лезет в Сеть;
* **installed** — содержит заголовочные и библиотечные файлы инсталлированных библиотек. Когда вы включаете интеграцию с VisualStudio, вы фактически добавляете эту папку к путям поиска;
* **packages** — внутренняя папка, используемая между установками;
* **ports** — файлы, описывающие каждую библиотеку в каталоге, её версию и адрес для скачивания. Можно добавлять собственные порты при необходимости;
* **scripts** — скрипты (cmake, powershell), используемые vcpkg;
* **toolsrc** — исходные коды для vcpkg и связанных компонентов;
* **triplets** — содержит настройки для каждой поддерживаемой платформы (например, x86-windows or x64-uwp).

В терминологии vcpkg триплетом называется сочетание архитектуры и платформы, под которые осуществляется сборка библиотеки. Доступные триплеты:

* arm-uwp
* arm-windows
* arm64-uwp
* arm64-windows
* x64-linux
* x64-osx
* x64-uwp
* x64-windows
* x64-windows-static
* x86-uwp
* x86-windows
* x86-windows-static.

В принципе, переносить vcpkg между машинами можно простым копированием папки, при условии, что на машинах используются идентичные тулсеты (например, одна и та же версия VS с совпадающими настройками).
