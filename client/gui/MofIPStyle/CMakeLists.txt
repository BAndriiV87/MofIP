cmake_minimum_required(VERSION 3.16)

set(This MofIPStyle)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set(HEADERS
    include/${This}.h
    include/StyleUtility.h
    include/DrawPrimitive.h
    include/DrawControl.h
    include/DrawComplexControl.h
)
set(SOURCES
    src/${This}.cpp
    src/StyleUtility.cpp
    src/DrawPrimitive.cpp
    src/DrawControl.cpp
    src/DrawComplexControl.cpp
)

add_library(${This} ${BUILD_TYPE} ${HEADERS} ${SOURCES})
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_folder(TARGET ${This})

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
