#
# Инструкция для сборки библиотеки интерфейса
#

# Минимальная версия CMake для исполнения данного скрипта
cmake_minimum_required(VERSION 3.10)

# Наименование проекта с указанием языка проекта С++
project(${APPNAME_LIB_INTERFACE} CXX)

# Формирование статической библиотеки интерфейса
add_library(${APPNAME_LIB_INTERFACE} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/interface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/interface_stream.cpp
)

# Указание расположения используемых заголовочных файлов
target_include_directories(${APPNAME_LIB_INTERFACE} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/env/resource/inc
	${CMAKE_SOURCE_DIR}/env/exception/inc
	${CMAKE_SOURCE_DIR}/env/implement/inc
)

# Указание для библиотеки интерфейса использования библиотеки для работы с исключениями
target_link_libraries(${APPNAME_LIB_INTERFACE} PRIVATE ${APPNAME_LIB_EXCEPTION})

# Выставление конечной директории для IDE
set_target_properties(${APPNAME_LIB_INTERFACE} PROPERTIES FOLDER "Lib")

# Выставление инструментария покрытия кода
if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows с использованием CLang
else()
	# Выставления для ОС Linux с использованием флагов g++
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Configuring for Debug build ${APPNAME_LIB_INTERFACE}.")
		target_compile_options(${APPNAME_LIB_INTERFACE} PRIVATE -g -O0)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(STATUS "Configuring for Release build ${APPNAME_LIB_INTERFACE}.")
		target_compile_options(${APPNAME_LIB_INTERFACE} PRIVATE -O0)
	else()
		message(FATAL_ERROR	"Now CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}\n"
							"Use -DCMAKE_BUILD_TYPE=Debug or -DCMAKE_BUILD_TYPE=Release")
	endif()
endif()
