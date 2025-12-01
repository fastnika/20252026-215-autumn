#!/bin/bash

# Конфигурация скрипта
BUILDDIR=out
BUILDCONFIG=Debug

# Команды скрипта
set -eu

if [ -d $BUILDDIR ]; then rm -r $BUILDDIR; fi
cmake -B $BUILDDIR -DCMAKE_BUILD_TYPE=$BUILDCONFIG
cmake --build $BUILDDIR