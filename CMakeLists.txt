cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("request_parser")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(request_parser
  main.cc request_parser.cc)

add_subdirectory(googletest)
add_executable(tests
  tests.cc request_parser.cc)
target_link_libraries(tests gtest_main)
add_test(tests tests)

file(GLOB LIBFUZZER_FILES ${CMAKE_SOURCE_DIR}/libFuzzer/*.cpp)
add_library(libFuzzer STATIC ${LIBFUZZER_FILES})
add_executable(fuzzer
  fuzzer.cc request_parser.cc)
target_link_libraries(fuzzer libFuzzer pthread)
set_target_properties(fuzzer PROPERTIES COMPILE_FLAGS "-fsanitize=address -fsanitize-coverage=edge,8bit-counters")
set_target_properties(fuzzer PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize-coverage=edge,8bit-counters")
