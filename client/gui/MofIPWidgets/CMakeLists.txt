cmake_minimum_required(VERSION 3.16)

set(This MofIPWidgets)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set(HEADERS
    include/MofIPWidgets.hpp
    include/MofIPWidgets/MofIPPushButton.hpp
    include/MofIPWidgets/MofipWidgetsCommon.hpp
    include/MofIPWidgets/MofIPWidgetsFactory.hpp
)
set(SOURCES
    src/MofIPPushButton.cpp
    src/MofipWidgetsCommon.cpp
    include/MofIPWidgets/MofIPWidgetsFactory.cpp
)

add_library(${This} ${BUILD_TYPE} ${HEADERS} ${SOURCES})
target_include_directories(${This} PUBLIC include)

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
