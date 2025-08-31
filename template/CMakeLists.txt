#
# Шаблон CMake-инструкций для автоматизированной сборки заданий
# ВНИМАНИЕ: ПРИ ИСПОЛЬЗОВАНИИ ДАННОГО ШАБЛОНА НЕОБХОДИМО ПРОВЕСТИ АДАПТАЦИЮ
#

# Примечание по формированию проекта:
#
# - Список доступных генераторов проекта (символом * указан генератор по умолчанию)
# $ cmake -G
#
# - Сборка с генератором по умолчанию в директорию out из директории расположения CMakeLists.txt в конфигурации Debug
#    по умолчанию в CMake для ОС Linux используется генератор - "Unix Makefiles"
#    по умолчанию в CMake для ОС Windows - "MinGW Makefiles", в случае наличия IDE Visual Studio 2022 - "Visual Studio 17 2022"
# $ cmake -B out -DCMAKE_BUILD_TYPE=Debug .
#
# - Сборка с генератором по умолчанию в директорию out из директории расположения CMakeLists.txt в конфигурации Release
#    конфигурация Debug служит для отладки программного обеспечения
#    конфигурация Release служит для формирования финального программного обеспечения
# $ cmake -B out -DCMAKE_BUILD_TYPE=Release .
#
# - Сборка с генереатором для IDE Visual Studio 2022 для ОС Windows в директорию out из директории расположения CMakeLists.txt
# $ cmake -G "Visual Studio 17 2022" -B out -DCMAKE_BUILD_TYPE=Debug .
#
# Примечание по сборке проекта:
# 
# - Автоматизированная сборка всех подпроектов проекта в директории out с использованием выбранного ранее генератора
# $ cmake --build out
#
# - Автоматизированная сборка выделенного подпроекта проекта в директории out с использованием выбранного ранее генератора
#  (наименование подпроекта должно совпадать с заданным TARGET первым параметром в add_executable())
# $ cmake --build out --target Example
#
# Примечание по комбинированным командам
#
# - Формирование и сборка проекта с генератором по умолчанию в директории out
# $ if [-d out]; then rm -r out; fi && cmake -B out -DCMAKE_BUILD_TYPE=Debug . && cmake --build out


# Минимальная версия CMake для исполнения данного скрипта
cmake_minimum_required(VERSION 3.10)

# Наименование проекта с указанием языка проекта С++
project(Example CXX)

# Стандарт используемого языка С++
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 14)

# Выставление локальных переменных для наименований выходных файлов
# (в качестве префикса используется отсылка на название проекта из внутренней переменной ${PROJECT_NAME})
set(APPNAME ${PROJECT_NAME})
set(APPNAME_SELFTEST ${PROJECT_NAME}_selftest)
set(APPNAME_LIB_INTERFACE ${PROJECT_NAME}_interface)
set(APPNAME_LIB_EXCEPTION ${PROJECT_NAME}_exception)
set(APPNAME_LIB_IMPLEMENTATION ${PROJECT_NAME}_implementation)
set(APPNAME_TEST_PREFIX ${PROJECT_NAME}_test_scenario)
set(APPNAME_SELFTEST_ENV ${APPNAME_SELFTEST}_prepare_env)

# Выставление локальной переменной OUTPUT_DIR для выставления выходной директории
# с указанием невозможности автоматического использования поддиреткорий (последовательность символов $<0:>)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)

if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows с использованием CLang
else()
	# Указание рекомендуемых флагов компиляции (для адаптации программы в компьютерном классе)
	# Примечание: Актуально для ОС Linux компилятора G++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security \
		-Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -Werror \
		-pedantic -pedantic-errors -Wunused -Wuninitialized --param inline-unit-growth=1000000 \
		--param max-inline-insns-single=10000000 --param large-function-growth=10000000 -fPIC")
endif()

# Указание расположения используемых заголовочных файлов
include_directories(
	${PROJECT_SOURCE_DIR}/env/interface/inc # Заголовочные файлы реализации для работы интерфейса
	${PROJECT_SOURCE_DIR}/env/exception/inc # Заголовочные файлы реализации для работы с исключениями
	${PROJECT_SOURCE_DIR}/env/resource/inc  # Заголовочные файлы реализации описываемых кодов ошибок
	${PROJECT_SOURCE_DIR}/env/implement/inc # Заголовочные файлы реализации производных классов
)

# Формирование статической библиотеки для работы с исключениями
add_library(${APPNAME_LIB_EXCEPTION} STATIC
	${PROJECT_SOURCE_DIR}/env/exception/src/base_exception.cpp
)

# Формирование статической библиотеки интерфейса
add_library(${APPNAME_LIB_INTERFACE} STATIC
	${PROJECT_SOURCE_DIR}/env/interface/src/interface.cpp
	${PROJECT_SOURCE_DIR}/env/interface/src/interface_stream.cpp
)

# Указание для библиотеки интерфейса использования библиотеки для работы с исключениями
target_link_libraries(${APPNAME_LIB_INTERFACE} PRIVATE ${APPNAME_LIB_EXCEPTION})

# Формирование статической библиотеки для работы с реализацией классов
add_library(${APPNAME_LIB_IMPLEMENTATION} STATIC
	${PROJECT_SOURCE_DIR}/env/implement/src/my_class.cpp
)

# Указание для библиотеки интерфейса использования библиотеки для работы с исключениями
target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE ${APPNAME_LIB_EXCEPTION})

# Формирование выходного исполняемого файла программы
add_executable(${APPNAME}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

# Указание для исполняемого файла программы библиотеки интерфейса и библиотеки реализации классов
target_link_libraries(${APPNAME} PRIVATE ${APPNAME_LIB_INTERFACE} ${APPNAME_LIB_IMPLEMENTATION})

# Формирование выходного исполняемого файла для самотестирования программы
add_executable(${APPNAME_SELFTEST}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

# Указание для исполняемого файла самотестирования программы библиотеки интерфейса и библиотеки реализации классов
target_link_libraries(${APPNAME_SELFTEST} PRIVATE ${APPNAME_LIB_INTERFACE} ${APPNAME_LIB_IMPLEMENTATION})

# Указание для исполняемого файла самотестирования определения макропеременной SELFTEST
target_compile_definitions(${APPNAME_SELFTEST} PRIVATE -DSELFTEST)

# Выставление инструментария покрытия кода
if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows с использованием CLang
else()
	# Выставления для ОС Linux с использованием флагов G++
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Configuring for Debug build.")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MODE")
		target_compile_options(${APPNAME_LIB_EXCEPTION} PRIVATE -g -O0)
		target_compile_options(${APPNAME_LIB_INTERFACE} PRIVATE -g -O0)
		target_compile_options(${APPNAME_LIB_IMPLEMENTATION} PRIVATE -g --coverage -O0)
		target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE gcov)
		target_compile_options(${APPNAME_SELFTEST} PRIVATE -g --coverage -O0)
		target_link_libraries(${APPNAME_SELFTEST} PRIVATE gcov)
		target_compile_options(${APPNAME} PRIVATE -g -O0)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(STATUS "Configuring for Release build.")
		target_compile_options(${APPNAME_LIB_EXCEPTION} PRIVATE -O0)
		target_compile_options(${APPNAME_LIB_INTERFACE} PRIVATE -O0)
		target_compile_options(${APPNAME_LIB_IMPLEMENTATION} PRIVATE --coverage -O0)
		target_link_libraries(${APPNAME_LIB_IMPLEMENTATION} PRIVATE gcov)
		target_compile_options(${APPNAME_SELFTEST} PRIVATE --coverage -O0)
		target_link_libraries(${APPNAME_SELFTEST} PRIVATE gcov)
		target_compile_options(${APPNAME} PRIVATE -O0)
	else()
		message(FATAL_ERROR	"Now CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}\n"
					"Use -DCMAKE_BUILD_TYPE=Debug or -DCMAKE_BUILD_TYPE=Release")
	endif()
endif()

# Копирование сценариев тестирования в директорию назначения и формирование списка 
file(GLOB LIST_SRC_TEST_SCENARIO "${PROJECT_SOURCE_DIR}/test/*.txt")
set(LIST_DST_TEST_SCENARIO)
foreach(ITEM_SRC_TEST_SCENARIO IN LISTS LIST_SRC_TEST_SCENARIO)
    get_filename_component(ITEM_SRC_TEST_SCENARIO_NAME ${ITEM_SRC_TEST_SCENARIO} NAME)
    set(ITEM_DST_TEST_SCENARIO "${OUTPUT_DIR}/test/${ITEM_SRC_TEST_SCENARIO_NAME}")
    add_custom_command(
	OUTPUT ${ITEM_DST_TEST_SCENARIO}
	COMMENT "COPY TEST SCENARIO TO ${ITEM_DST_TEST_SCENARIO}"
	COMMAND ${CMAKE_COMMAND} -E copy ${ITEM_SRC_TEST_SCENARIO} ${ITEM_DST_TEST_SCENARIO}
    )
    list(APPEND LIST_DST_TEST_SCENARIO ${ITEM_DST_TEST_SCENARIO})
endforeach()

add_custom_target(${APPNAME_SELFTEST_ENV} ALL DEPENDS ${LIST_DST_TEST_SCENARIO} )

# Предварительная очистка окружения от ранее сформированного инструментария покрытия кода 
if(MSVC)
    # Для ОС Windows инструментарий покрытия кода не очищается, т.к. не произведена инициализация ранее
else()
    add_custom_command(
	TARGET ${APPNAME_SELFTEST_ENV} PRE_BUILD
	COMMENT "CLEAR COVERAGE"
	COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_BINARY_DIR}/*.gcov"
    )
endif()

# Для выходного исполняемого файла самотестирования произвести предварительную очистку
add_dependencies(${APPNAME_SELFTEST} ${APPNAME_SELFTEST_ENV})

# Включение инструментария самотестирования CTest и автоматизированное добавление всех сценариев тестирования 
enable_testing()
set(i 0)
foreach(ITEM_DST_TEST_SCENARIO ${LIST_DST_TEST_SCENARIO})
    if(MSVC)
		# Для ОС Windows запуск теста без инструментария valgrind
		add_test(
			NAME ${APPNAME_TEST_PREFIX}_${i}
			COMMAND ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${ITEM_DST_TEST_SCENARIO}
		)
    else()
		# Для ОС Linux запуск теста с инструментарием valgrind и указанием мест утечек памяти дополнительными параметрами
		add_test(
			NAME ${APPNAME_TEST_PREFIX}_${i}
			COMMAND valgrind --leak-check=full --show-leak-kinds=all ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${ITEM_DST_TEST_SCENARIO}
		)
    endif()

	# Указание директории назначения для выполнения
    set_tests_properties(
		${APPNAME_TEST_PREFIX}_${i} PROPERTIES
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # Увеличиваем счетчик на 1 для наименования очередного теста
    math(EXPR i "${i} + 1")
endforeach()

# Указание для самотестирования запуска 
add_custom_command(TARGET ${APPNAME_SELFTEST} POST_BUILD
    COMMENT "RUN CTEST"
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(MSVC)
    # Для ОС Windows не производятся дополнительные команды по построению coverage
else()
	# Действия для ОС Linux
	
	# Выполнение действий формирования информации по покрытию кода
    add_custom_command(
		TARGET ${APPNAME_SELFTEST} POST_BUILD
		COMMENT "CREATE COVERAGE"
		COMMAND bash -c 'find . -name \*.gcda -exec gcov \{\} \\\;'
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

	# Выполнение действий после формирования информации по покрытию кода
    add_custom_command(
		TARGET ${APPNAME_SELFTEST} POST_BUILD
		COMMENT "CHECK COVERAGE"
		COMMAND bash -c 'for f in $$\(find ${PROJECT_SOURCE_DIR} -type f -name \*.cpp -exec basename \{\}.gcov \\\;\)\; do if [ -e $$f ]; then echo CHECK COVERAGE $$f\; grep -C5 \"\#\#\#\#\#\" $$f\; fi\; done'
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
