#
# Инструкция для сборки библиотеки при реализации классов для решения задачи
#

# Минимальная версия CMake для исполнения данного скрипта
cmake_minimum_required(VERSION 3.10)

# Наименование проекта с указанием языка проекта С++
project(${APPNAME_LIB_IMPLEMENTATION} CXX)

# Формирование статической библиотеки для работы с реализацией классов
add_library(${APPNAME_LIB_IMPLEMENTATION} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/my_class.cpp
)

# Указание расположения используемых заголовочных файлов
target_include_directories(${APPNAME_LIB_IMPLEMENTATION} PUBLIC
	${CMAKE_SOURCE_DIR}/env/exception/inc   # Заголовочные файлы реализации для работы с исключениями
	${CMAKE_SOURCE_DIR}/env/resource/inc    # Заголовочные файлы реализации описываемых кодов ошибок
	${CMAKE_CURRENT_SOURCE_DIR}/inc         # Заголовочные файлы реализации классов для решения задачи
)

# Указание для библиотеки интерфейса использования библиотеки для работы с исключениями
target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE ${APPNAME_LIB_EXCEPTION})

# Выставление конечной директории для IDE
set_target_properties(${APPNAME_LIB_IMPLEMENTATION} PROPERTIES FOLDER "Lib")

# Выставление инструментария покрытия кода
if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows с использованием CLang
else()
	# Выставления для ОС Linux с использованием флагов g++
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Configuring for Debug build ${APPNAME_LIB_IMPLEMENTATION}.")
		target_compile_options(${APPNAME_LIB_IMPLEMENTATION} PRIVATE -g --coverage -O0)
		target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE gcov)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(STATUS "Configuring for Release build ${APPNAME_LIB_IMPLEMENTATION}.")
		target_compile_options(${APPNAME_LIB_IMPLEMENTATION} PRIVATE --coverage -O0)
		target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE gcov)
	else()
		message(FATAL_ERROR	"Now CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}\n"
							"Use -DCMAKE_BUILD_TYPE=Debug or -DCMAKE_BUILD_TYPE=Release")
	endif()
endif()
