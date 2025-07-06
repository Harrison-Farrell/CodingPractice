cmake_minimum_required(VERSION 3.5)

project(CodingPractice)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(LoggerRateLimter problems/LoggerRateLimiter.cpp)
add_executable(AddTwoNumbers problems/AddTwoNumbers.cpp)
add_executable(HitCounter problems/HitCounter.cpp)

set_target_properties(
  LoggerRateLimter
  AddTwoNumbers
  HitCounter
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

