cmake_minimum_required(VERSION 3.16)

set(This mofipobjects)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set_library_type_msvc()

set(HEADERS
    include/${This}.hpp
    include/${This}/IOperation.hpp
)
set(SOURCES
    src/Operation.cpp
)

add_library(${This} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET ${This} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS true)

set_target_folder(TARGET ${This})

#install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
