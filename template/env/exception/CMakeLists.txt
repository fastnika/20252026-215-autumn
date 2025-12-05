#
# Инструкция для сборки библиотеки для работы с исключениями
#

# Минимальная версия CMake для исполнения данного скрипта
cmake_minimum_required(VERSION 3.10)

# Наименование проекта с указанием языка проекта С++
# Примечание: предполагается переменная определена в головном CMakeLists.txt
project(${APPNAME_LIB_EXCEPTION} CXX)

# Формирование статической библиотеки для работы с исключениями
add_library(${APPNAME_LIB_EXCEPTION} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/base_exception.cpp
)

# Указание расположения используемых заголовочных файлов
target_include_directories(${APPNAME_LIB_EXCEPTION} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc # Заголовочные файлы реализации для работы с исключениями
)

# Выставление конечной директории для IDE
set_target_properties(${APPNAME_LIB_EXCEPTION} PROPERTIES FOLDER "Lib")

# Выставление инструментария покрытия кода
if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows с использованием CLang
else()
	# Выставления для ОС Linux с использованием флагов g++
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Configuring for Debug build ${APPNAME_LIB_EXCEPTION}.")
		target_compile_options(${APPNAME_LIB_EXCEPTION} PRIVATE -g -O0)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(STATUS "Configuring for Release build ${APPNAME_LIB_EXCEPTION}.")
		target_compile_options(${APPNAME_LIB_EXCEPTION} PRIVATE -O0)
	else()
		message(FATAL_ERROR	"Now CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}\n"
							"Use -DCMAKE_BUILD_TYPE=Debug or -DCMAKE_BUILD_TYPE=Release")
	endif()
endif()
