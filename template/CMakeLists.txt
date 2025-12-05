#
# CMake-инструкции для сборки проекта Polygon (Final Version)
#

cmake_minimum_required(VERSION 3.10)
project(Example CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Выставление глобальных переменных для наименований выходных файлов
set(APPNAME ${PROJECT_NAME})
set(APPNAME_SELFTEST ${PROJECT_NAME}_selftest)
set(APPNAME_LIB_INTERFACE ${PROJECT_NAME}_interface)
set(APPNAME_LIB_EXCEPTION ${PROJECT_NAME}_exception)
set(APPNAME_LIB_IMPLEMENTATION ${PROJECT_NAME}_implementation)
set(APPNAME_TEST_PREFIX ${PROJECT_NAME}_test_scenario)
set(APPNAME_SELFTEST_ENV ${APPNAME_SELFTEST}_prepare_env)

# Выставление выходной директории
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>)

if(MSVC)
	# Выставления для IDE Visual Studio ОС Windows
else()
	# Указание флагов компиляции для Linux G++
	message(STATUS "Configuring Linux CXX Flags.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security \
		-Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -Werror \
		-pedantic -pedantic-errors -Wunused -Wuninitialized --param inline-unit-growth=1000000 \
		--param max-inline-insns-single=10000000 --param large-function-growth=10000000 -fPIC")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Configuring for Debug build CXX Flags.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MODE")
endif()

# Указание расположения используемых заголовочных файлов
set(INPUT_INC_DIR
	${PROJECT_SOURCE_DIR}/env/interface/inc
	${PROJECT_SOURCE_DIR}/env/exception/inc
	${PROJECT_SOURCE_DIR}/env/resource/inc
	${PROJECT_SOURCE_DIR}/env/implement/inc
)

# Формирование основного исполняемого файла программы
add_executable(${APPNAME}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(${APPNAME} PUBLIC ${INPUT_INC_DIR})
target_link_libraries(${APPNAME} PRIVATE ${APPNAME_LIB_INTERFACE} ${APPNAME_LIB_IMPLEMENTATION})

# Формирование самотестирующегося исполняемого файла
add_executable(${APPNAME_SELFTEST}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(${APPNAME_SELFTEST} PUBLIC ${INPUT_INC_DIR})
target_link_libraries(${APPNAME_SELFTEST} PRIVATE ${APPNAME_LIB_INTERFACE} ${APPNAME_LIB_IMPLEMENTATION})
target_compile_definitions(${APPNAME_SELFTEST} PRIVATE -DSELFTEST)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${APPNAME} PROPERTIES FOLDER "App")
set_target_properties(${APPNAME_SELFTEST} PROPERTIES FOLDER "App")

# Инструкции для сборки библиотек
add_subdirectory(${PROJECT_SOURCE_DIR}/env/exception)
add_subdirectory(${PROJECT_SOURCE_DIR}/env/implement)
add_subdirectory(${PROJECT_SOURCE_DIR}/env/interface)

# Выставление инструментария покрытия кода
if(MSVC)
	# Выставления для IDE Visual Studio
else()
	# Выставления для ОС Linux
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Configuring for Debug build ${APPNAME}.")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MODE")
		target_compile_options(${APPNAME_SELFTEST} PRIVATE -g --coverage -O0)
		target_link_libraries(${APPNAME_SELFTEST} PRIVATE gcov)
		target_compile_options(${APPNAME} PRIVATE -g -O0)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(STATUS "Configuring for Release build ${APPNAME}.")
		target_compile_options(${APPNAME_SELFTEST} PRIVATE --coverage -O0)
		target_link_libraries(${APPNAME_SELFTEST} PRIVATE gcov)
		target_compile_options(${APPNAME} PRIVATE -O0)
	else()
		message(FATAL_ERROR	"Now CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}\n"
							"Use -DCMAKE_BUILD_TYPE=Debug or -DCMAKE_BUILD_TYPE=Release")
	endif()
endif()

# Копирование сценариев тестирования в директорию назначения
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

add_custom_target(${APPNAME_SELFTEST_ENV} ALL DEPENDS ${LIST_DST_TEST_SCENARIO})
set_target_properties(${APPNAME_SELFTEST_ENV} PROPERTIES FOLDER "Util")

# Предварительная очистка окружения от покрытия кода
if(MSVC)
	# Для ОС Windows не производятся
else()
	add_custom_command(
		TARGET ${APPNAME_SELFTEST_ENV} PRE_BUILD
		COMMENT "CLEAR COVERAGE"
		COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_BINARY_DIR}/*.gcov"
	)
endif()

add_dependencies(${APPNAME_SELFTEST} ${APPNAME_SELFTEST_ENV})

# Включение тестирования CTest
enable_testing()
set(i 1) # Начинаем с 1, как в эталоне
foreach(ITEM_DST_TEST_SCENARIO ${LIST_DST_TEST_SCENARIO})
	if(MSVC)
		add_test(
			NAME ${APPNAME_TEST_PREFIX}_${i}
			COMMAND ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${ITEM_DST_TEST_SCENARIO}
		)
	else()
		add_test(
			NAME ${APPNAME_TEST_PREFIX}_${i}
			COMMAND valgrind --leak-check=full --show-leak-kinds=all ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${ITEM_DST_TEST_SCENARIO}
		)
	endif()

	set_tests_properties(
		${APPNAME_TEST_PREFIX}_${i} PROPERTIES
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)

	math(EXPR i "${i} + 1")
endforeach()

# Запуск CTest после сборки
add_custom_command(TARGET ${APPNAME_SELFTEST} POST_BUILD
	COMMENT "RUN CTEST"
	COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose --output-on-failure
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(MSVC)
	# Для ОС Windows не производятся
else()
	# Генерация покрытия кода
	add_custom_command(
		TARGET ${APPNAME_SELFTEST} POST_BUILD
		COMMENT "CREATE COVERAGE"
		COMMAND bash -c 'find . -name \*.gcda -exec gcov \{\} \\\;'
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)

		# Проверка покрытия кода
	add_custom_command(
		TARGET ${APPNAME_SELFTEST} POST_BUILD
		COMMENT "CHECK COVERAGE"
		COMMAND bash -c 'ls -la *.cpp.gcov 2>/dev/null | head -5 || echo "No coverage files yet"'
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
endif()

# Добавление CTAGS (из эталона)
if(NOT MSVC AND ENABLING_CTAGS)
    add_custom_command(
	OUTPUT ${CMAKE_SOURCE_DIR}/CTAGS
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMAND ctags -R --c-kinds=+lzp --fields=+iaS --exclude=${CMAKE_BINARY_DIR} --extras=+q -e .
    )
    add_custom_target(generate_ctags ALL DEPENDS ${CMAKE_SOURCE_DIR}/CTAGS)
    add_dependencies(${APPNAME} generate_ctags)
endif()
