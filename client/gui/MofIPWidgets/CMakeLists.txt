cmake_minimum_required(VERSION 3.16)

set(This MofIPWidgets)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set(HEADERS
    include/MofIPWidgets/SimpleWidget.hpp
)
set(SOURCES
    src/SimpleWidget.cpp
)

set(BUILD_TYPE STATIC)
if(GUI_BUILD_SHARED_LIBRARY)
    set(BUILD_TYPE SHARED)
    init_library_msvc(SHARED_LIB)
else(GUI_BUILD_SHARED_LIBRARY)
    init_library_msvc()
endif(GUI_BUILD_SHARED_LIBRARY)

add_library(${This} ${BUILD_TYPE} ${HEADERS} ${SOURCES})
target_link_libraries(${This} 
    PRIVATE 
        Qt5::Widgets
)
target_include_directories(${This} PUBLIC include)
