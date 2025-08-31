#!/bin/bash

#
# Конфигурация скрипта для ОС Linux
#

# Директория построения
BUILDDIR=out
# Конфигурация построения
BUILDCONFIG=Debug
#BUILDCONFIG=Release

#
# Команды скрипта для ОС Linux
#

# Выставление параметров для текущего скрипта при некорреткном завершении предшествующей команды
set -eu

# Очистка директории построения при наличии
if [[ -d $BUILDDIR ]]; then rm -r $BUILDDIR; fi

# Формирование проекта
cmake -B $BUILDDIR -DCMAKE_BUILD_TYPE=$BUILDCONFIG .

# Формирование проекта c CodeJump CTAGS
#cmake -B $BUILDDIR -DCMAKE_BUILD_TYPE=$BUILDCONFIG -DENABLING_CTAGS=1 .

# Построение проекта
cmake --build $BUILDDIR
