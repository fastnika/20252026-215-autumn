cmake_minimum_required(VERSION 3.10)
project(Example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(env/exception)
add_subdirectory(env/implement)
add_subdirectory(env/interface)

add_executable(Example src/main.cpp)
target_link_libraries(Example PRIVATE exception interface implement)
target_compile_options(Example PRIVATE $<$<CONFIG:Debug>:-g -O0> $<$<CONFIG:Release>:-O3>)

add_executable(Example_selftest src/main.cpp)
target_compile_definitions(Example_selftest PRIVATE SELFTEST)
target_link_libraries(Example_selftest PRIVATE exception interface implement)
target_compile_options(Example_selftest PRIVATE $<$<CONFIG:Debug>:-g -O0> $<$<CONFIG:Release>:-O3>)

# Копируем тестовые файлы в выходную папку
file(COPY test/test_scenario_01.txt DESTINATION ${CMAKE_BINARY_DIR}/bin/test/)
file(COPY test/test_scenario_02.txt DESTINATION ${CMAKE_BINARY_DIR}/bin/test/)

enable_testing()
add_test(NAME Example_test_scenario_0
  COMMAND Example_selftest "bin/test/test_scenario_01.txt"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_test(NAME Example_test_scenario_1
  COMMAND Example_selftest "bin/test/test_scenario_02.txt"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)