rem
rem Конфигурация скрипта для OC Windows
rem

rem Выставление кодировки UTF8
chcp 65001

rem
rem Команды скрипта для OC Windows
rem

rem Директория построения
set BUILDDIR=out

rem Очистка директории построения при наличии
if exist %BUILDDIR% del /S /Q %BUILDDIR%

rem Формирование проекта
cmake -B %BUILDDIR% .

rem Построение проекта
cmake --build %BUILDDIR%
