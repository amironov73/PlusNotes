### LCC

https://ru.wikipedia.org/wiki/LCC

LCC (акроним от «Local C Compiler» или «Little C Compiler») — небольшой адаптируемый ANSI C компилятор, имеющий лицензию, которая запрещает его коммерческое распространение и требует покупки лицензии для любого коммерческого использования. Позволяет быстро сгенерировать код для платформ DEC Alpha, SPARC, MIPS R3000, x86, SGI N32, Multiclet, а также для платформы .Net.

Реализация описана в книге A Retargetable C Compiler: Design and Implementation (ISBN 0-8053-1670-1).

Исходный код компилятора LCC часто используют, когда требуется компиляция с языка, близкого к Си на ту или иную платформу (например, в байт-код виртуальной машины). Именно так использован LCC в Quake III (см. QuakeC).

#### LCC-Win32

Компилятор и IDE LCC-Win32 в настоящее время развивается немецкой фирмой Q Software Solution как коммерческое ПО, бесплатное для персонального использования. Ею так же разработаны LCC-Win64 и lcc-linux32.

Входной язык LCC-Win32 — это версия Си, расширенная некоторыми возможностями, характерными для С++, такими как перегрузка операций, (ограниченная) перегрузка функций, декларация переменных в любом месте блока, подставляемые (inline) функции, работа с исключениями. Однако синтаксис и семантика этих расширений отличаются от принятых в C++.
