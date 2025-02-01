cmake_minimum_required(VERSION 3.0)
project(test)

option(testEquationSolution "test testEquationSolution function" ON)
option(correctA "test correctA function" ON)
option(noRoot "test noRoot function" ON)
option(noRoot "test oneRoot function" ON)
option(noRoot "test twoRoot function" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")

add_executable(main main.cpp)
target_include_directories(main PRIVATE include)
target_compile_definitions(
  main PRIVATE
  $<$<BOOL:${testEquationSolution}>:testEquationSolution>
  $<$<BOOL:${correctA}>:correctA>
  $<$<BOOL:${noRoot}>:noRoot>
  $<$<BOOL:${oneRoot}>:oneRoot>
  $<$<BOOL:${twoRoot}>:twoRoot>
)

enable_testing()
add_test(NAME main COMMAND $<TARGET_FILE:main>)
