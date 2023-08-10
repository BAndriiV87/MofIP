cmake_minimum_required(VERSION 3.15)

set(This temp)

set(Headers
    include/temp/temp.hpp
)

set(Sources
    src/temp.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

target_include_directories(${This} PUBLIC include)

#add_subdirectory(test)
