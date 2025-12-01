# CMake generated Testfile for 
# Source directory: /home/airat/20252026-215-autumn/template
# Build directory: /home/airat/20252026-215-autumn/template/out
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example_test_scenario_0 "/home/airat/20252026-215-autumn/template/out/bin/Example_selftest" "bin/test/test_scenario_01.txt")
set_tests_properties(Example_test_scenario_0 PROPERTIES  WORKING_DIRECTORY "/home/airat/20252026-215-autumn/template/out" _BACKTRACE_TRIPLES "/home/airat/20252026-215-autumn/template/CMakeLists.txt;36;add_test;/home/airat/20252026-215-autumn/template/CMakeLists.txt;0;")
add_test(Example_test_scenario_1 "/home/airat/20252026-215-autumn/template/out/bin/Example_selftest" "bin/test/test_scenario_02.txt")
set_tests_properties(Example_test_scenario_1 PROPERTIES  WORKING_DIRECTORY "/home/airat/20252026-215-autumn/template/out" _BACKTRACE_TRIPLES "/home/airat/20252026-215-autumn/template/CMakeLists.txt;40;add_test;/home/airat/20252026-215-autumn/template/CMakeLists.txt;0;")
subdirs("env/exception")
subdirs("env/implement")
subdirs("env/interface")
