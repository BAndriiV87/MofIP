cmake_minimum_required(VERSION 3.16)

set(This MofIPGui)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set(HEADERS
    include/MofIPGui.hpp
    include/MofIPGui/MainWindow.hpp
)
set(SOURCES
    src/MainWindow.cpp
)

add_library(${This} ${BUILD_TYPE} ${HEADERS} ${SOURCES})
target_link_libraries(${This} 
    PRIVATE 
        MofIPWidgets
)
target_include_directories(${This} 
    PUBLIC 
        include
)

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
