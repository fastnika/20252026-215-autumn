cmake_minimum_required(VERSION 3.10)

project(Example CXX)

# Выставление локальных переменных для наименований выходных файлов
# (в качестве префикса используется отсылка на название проекта из внутренней переменной ${PROJECT_NAME})
set(APPNAME ${PROJECT_NAME})
set(APPNAME_SELFTEST ${PROJECT_NAME}_selftest)
set(APPNAME_LIB_INTERFACE ${PROJECT_NAME}_interface)
set(APPNAME_TEST_PREFIX ${PROJECT_NAME}_test_scenario)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


include_directories(
	${PROJECT_SOURCE_DIR}/env/interface/inc
)

add_library(${APPNAME_LIB_INTERFACE} STATIC 
	${PROJECT_SOURCE_DIR}/env/interface/src/interface.cpp
	${PROJECT_SOURCE_DIR}/env/interface/src/interface_stream.cpp
)

add_executable(${APPNAME}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(${APPNAME} PRIVATE ${APPNAME_LIB_INTERFACE})

add_executable(${APPNAME_SELFTEST}
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(${APPNAME_SELFTEST} PRIVATE ${APPNAME_LIB_INTERFACE})

target_compile_definitions(${APPNAME_SELFTEST} PRIVATE -DSELFTEST)
if(MSVC)
	# Для Windows данный инструментарий может быть посмотрен для CLang
else()
	target_compile_options(${APPNAME_LIB_INTERFACE} PRIVATE -g -O0)
	target_compile_options(${APPNAME_SELFTEST} PRIVATE -g --coverage -O0)
	target_link_libraries(${APPNAME_SELFTEST} PRIVATE gcov)
endif()

#add_custom_command(
##add_custom_target(
##	TARGET ${APPNAME_SELFTEST} PRE_BUILD
#	OUTPUT ${OUTPUT_DIR}/test
##	${APPNAME_SELFTEST}_prepare_env
#	#COMMAND ${CMAKE_COMMAND} -E echo "[PRE_BUILD] COPY TEST SCENARIO"
#	COMMENT "COPY TEST SCENARIO"
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test ${OUTPUT_DIR}/test
##	COMMENT "CLEAR COVERAGE"
##	COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/*.gcov"
#)

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

#add_custom_target(${APPNAME_SELFTEST}_prepare_env ALL DEPENDS ${CMAKE_BINARY_DIR} ${OUTPUT_DIR}/test)
add_custom_target(${APPNAME_SELFTEST}_prepare_env ALL DEPENDS ${LIST_DST_TEST_SCENARIO} )

add_custom_command(
#	OUTPUT ${CMAKE_BINARY_DIR}
	TARGET ${APPNAME_SELFTEST}_prepare_env PRE_BUILD
#	COMMAND ${CMAKE_COMMAND} -E echo "[PRE_BUILD] COPY TEST SCENARIO"
#	COMMENT "COPY TEST SCENARIO"
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test ${OUTPUT_DIR}/test
	COMMENT "CLEAR COVERAGE"
	COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_BINARY_DIR}/*.gcov"
)

add_dependencies(${APPNAME_SELFTEST} ${APPNAME_SELFTEST}_prepare_env)

enable_testing()
#file(GLOB test_scenario_list "${PROJECT_SOURCE_DIR}/test/*.txt")
#file(GLOB test_scenario_list "${OUTPUT_DIR}/test/*.txt")
set(i 0)
#foreach(test_scenario_item ${test_scenario_list})
foreach(ITEM_DST_TEST_SCENARIO ${LIST_DST_TEST_SCENARIO})
    add_test(
	NAME ${APPNAME_TEST_PREFIX}_${i}
#	COMMAND valgrind --leak-check=full --show-leak-kinds=all ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${test_scenario_item}
	COMMAND valgrind --leak-check=full --show-leak-kinds=all ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${ITEM_DST_TEST_SCENARIO}
    )
    set_tests_properties(${APPNAME_TEST_PREFIX}_${i} PROPERTIES
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # Увеличиваем счетчик на 1
    math(EXPR i "${i} + 1")
endforeach()

#add_test(NAME ${APPNAME_TEST_PREFIX}_01 
#    COMMAND valgrind ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${OUTPUT_DIR}/test/test_scenario_01.txt)
#add_test(NAME ${APPNAME_TEST_PREFIX}_02
#    COMMAND valgrind ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${OUTPUT_DIR}/test/test_scenario_02.txt)

add_custom_command(TARGET ${APPNAME_SELFTEST} POST_BUILD
    COMMENT "RUN CTEST"
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ${APPNAME_SELFTEST} POST_BUILD
    COMMENT "CREATE COVERAGE"
    COMMAND bash -c 'find . -name \*.gcda -exec gcov \{\} \\\;'
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ${APPNAME_SELFTEST} POST_BUILD
    COMMENT "CHECK COVERAGE"
    COMMAND bash -c 'for f in $$\(find ${PROJECT_SOURCE_DIR} -type f -name \*.cpp -exec basename \{\}.gcov \\\;\)\; do if [ -e $$f ]; then echo CHECK COVERAGE $$f\; grep -C5 \"\#\#\#\#\#\" $$f\; fi\; done'
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)


#file(GLOB test_scenario_list "${OUTPUT_DIR}/test/*.txt")
#set(i 0)
#foreach(test_scenario_item ${test_scenario_list})
#    add_test(NAME ${APPNAME_TEST_PREFIX}_${i} COMMAND ${OUTPUT_DIR}/${APPNAME_SELFTEST} ${OUTPUT_DIR}/test/${test_scenario_item})
    
	# Увеличиваем счетчик на 1
#	math(EXPR i "${i} + 1")
#endforeach()
