cmake_minimum_required(VERSION 3.0)
project(test)

option(test "test test1 function" ON)
option(test "test test2 function" ON)
option(test "test test3 function" ON)
option(test "test test4 function" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")

add_executable(main main.cpp include/CommandFuelBurn.cpp include/CommandFuelCheck.cpp include/CommandLoger.cpp include/CommandMove.cpp include/CommandQueue.cpp include/CommandRepeat.cpp include/CommandRotate.cpp include/CommandSimpleMacro.cpp include/ExceptionHandler.cpp include/object.cpp)
target_include_directories(main PRIVATE include)
target_compile_definitions(
  main PRIVATE
  $<$<BOOL:${test}>:test1>
  $<$<BOOL:${test}>:test2>
  $<$<BOOL:${test}>:test3>
  $<$<BOOL:${test}>:test4>
)

enable_testing()
add_test(NAME main COMMAND $<TARGET_FILE:main>)
