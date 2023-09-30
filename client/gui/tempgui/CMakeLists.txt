cmake_minimum_required(VERSION 3.16)

set(This tempgui)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set_library_type_msvc(SHARED_LIB)

set(HEADERS
    include/${This}.hpp
    include/temp.hpp
    include/mythread.hpp
)
set(SOURCES
    src/temp.cpp
    src/mythread.cpp
)

add_library(${This} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET ${This} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS true)

set_target_folder(TARGET ${This})

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
