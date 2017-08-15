# AmberInstaller
Тестовое задание

Простой распаковщик zip архива с игрой.
После запуска программы и нажатии кнопки "Extract" - архив с игрой копируется во временную директорию, затем распаковывается и запускается исполняемый exe файл игры.

Используется библиотеку libzip. Интерфейс написан с использованием Qt

# Инструкция по сборке

Сборку программы лучше производить используя компилятор g++ входящий в MinGw32. Вся сборка может производится в консоли Qt, или при использовании обычной консоли Windows, путь к Qt должен быть в системной переменной PATH.

В корне проекта запускаем qmake, который сгенерирует Makefile
```
qmake AmberInstaller.pro -r -spec win32-g++ "CONFIG+=release"
```
Теперь можно компилировать
```
mingw32-make
```
В директории release долже появится испольняемый файл AmberInstaller.exe
Если на компьютере используется стандартная установка Qt, то для запуска в директории, где находится исполняемый файл, должны находится следующие библиотеки:

* libgcc_s_dw2-1.dll
* icudt53.dll
* icuin53.dll
* icuuc53.dll
* libstdc++-6.dll
* Qt5Core.dll
* Qt5Gui.dll
* Qt5Widgets.dll
* libgcc_s_dw2-1.dll
* libstdc++-6.dll

Если хочется собрать исполняемый файл без зависимостей от этих библиотек, то нужно собирать Qt из исходников (https://wiki.qt.io/Building_a_static_Qt_for_Windows_using_MinGW)

# Возможные ошибки при компиляции

Если, при сборке программы компилятор не может найти файл "unistd.h" в lib/zlib/zconf.h
```
Cannot open include file: 'unistd.h': No such file or directory
```
Для решения этой проблемы, можно просто заменить в файле lib/zlib/zconf.h в строке 287 единицу на ноль, так как файл unistd.h для windows не используется

Файл lib/zlib/zconf.h перед редактированием
```
287 #if 1           /* HAVE_UNISTD_H -- this line is updated by ./configure */
288 #  include <sys/types.h> /* for off_t */
289 #  include <unistd.h>    /* for SEEK_* and off_t */
290 #  ifdef VMS
291 #    include <unixio.h>   /* for off_t */
292 #  endif
293 #  define z_off_t off_t
294 #endif
```
После редактирования
```
287 #if 0           /* HAVE_UNISTD_H -- this line is updated by ./configure */
```
