### Musl

https://ru.wikipedia.org/wiki/Musl

musl — реализация стандартной библиотеки для языка Си (libc), предназначенная для операционных систем на основе ядра Linux, распространяемая под лицензией MIT. Библиотека разработана в начале 2010-х Ричем Фелкером в качестве чистой и эффективной реализации, соответствующей стандартам.

Библиотека Musl была написана с нуля, без переиспользования существующего кода. При её написании уделялось внимание эффективному статическому связыванию, качеству для систем, близких к реальному времени. Автор старался избегать сложных внутренних сбоев при исчерпании ресурсов, проблем с синхронизацией и примеров некачественного поведения, присутствующих в ряде существовавших на тот момент реализаций. Скомпилированная библиотека представляет собой единственный динамический объектный файл со стабильным интерфейсом (ABI), что упрощает обновления. Также имеется версия для статического связывания, что позволяет создавать портативные приложения в виде одного исполняемого файла без внешних зависимостей.

Заявлена совместимость со спецификацией POSIX 2008 и стандартом языка C11. Также в musl реализованы многие нестандартные наборы библиотечных функций, используемые в Линукс, BSD и реализованные в glibc.

Среди дистрибутивов Linux, которые могут использовать musl в качестве стандартной библиотеки libc: Alpine Linux, Dragora 3, OpenWRT, Sabotage, Morpheus Linux и Void Linux.
