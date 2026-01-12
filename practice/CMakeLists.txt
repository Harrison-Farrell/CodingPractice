include(Practice)

AddPractice(StockPriceFluctuation)
AddPractice(MeetingRoomsII)
AddPractice(RankTeamsByVotes)
AddPractice(KokoEatingBananas)
AddPractice(MergeIntervals)
AddPractice(LowestCommonAncestor)
AddPractice(DesignSnakeGame)


include(AVS_Installer)
add_custom_target(avs-install)

add_executable(Hello hello_world.cpp)

AVS_Installer(Hello "${CMAKE_BINARY_DIR}/bin/test" "avs-install")
