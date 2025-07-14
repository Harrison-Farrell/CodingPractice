cmake_minimum_required(VERSION 3.10)

project(CodingPractice)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(LoggerRateLimter problems/LoggerRateLimiter.cpp)
add_executable(AddTwoNumbers problems/AddTwoNumbers.cpp)
add_executable(HitCounter problems/HitCounter.cpp)
add_executable(TwoSum problems/TwoSum.cpp)
add_executable(PalindromeNumber problems/PalindromeNumber.cpp)
add_executable(LongestCommonPrefix problems/LongestCommonPrefix.cpp)
add_executable(MaximumNumberOfWordsYouCanType problems/MaximumNumberOfWordsYouCanType.cpp)
add_executable(EditDistance problems/EditDistance.cpp)

set_target_properties(
  LoggerRateLimter
  AddTwoNumbers
  HitCounter
  TwoSum
  PalindromeNumber
  LongestCommonPrefix
  MaximumNumberOfWordsYouCanType
  EditDistance
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

