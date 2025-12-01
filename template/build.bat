@echo off
REM Конфигурация скрипта
set BUILDDIR=out
set BUILDCONFIG=Debug

REM Очистка директории построения при наличии
if exist %BUILDDIR% rmdir /s /q %BUILDDIR%

REM Формирование проекта
cmake -B %BUILDDIR% -DCMAKE_BUILD_TYPE=%BUILDCONFIG%

REM Построение проекта
cmake --build %BUILDDIR%