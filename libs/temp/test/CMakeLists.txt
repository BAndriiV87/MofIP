cmake_minimum_required(VERSION 3.15)

set(This TempTest)

set(Sources
    src/tempTest.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_link_libraries(${This} PUBLIC
    gtest_main
    temp
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
