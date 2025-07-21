add_executable(StockPriceFluctuation 2034_StockPriceFluctuation.cpp)
add_executable(MeetingRoomsII 253_MeetingRoomsII.cpp)
add_executable(DesignSnakeGame 353_DesignSnakeGame.cpp)
add_executable(HighAccessEmployees 2933_HighAccessEmployees.cpp)

set_target_properties(
  StockPriceFluctuation
  MeetingRoomsII
  DesignSnakeGame
  HighAccessEmployees
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)