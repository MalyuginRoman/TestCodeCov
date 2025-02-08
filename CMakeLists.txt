cmake_minimum_required(VERSION 3.0)
project(test)

option(test "test test1 function" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")

add_executable(main main.cpp src/com/icommand.cpp src/sec/object.cpp src/spe/eventloop.cpp src/spe/exceptionhandler.cpp src/spe/istate.cpp src/com/movecommand.cpp src/sec/producer.cpp)
target_include_directories(main PRIVATE include)
target_compile_definitions(
  main PRIVATE
  $<$<BOOL:${test}>:test1>
)

enable_testing()
add_test(NAME main COMMAND $<TARGET_FILE:main>)
