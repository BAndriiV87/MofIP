cmake_minimum_required(VERSION 3.16)

set(This mofipwidgets)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set_library_type_msvc(SHARED_LIB)

set(HEADERS
    include/${This}.hpp
    include/startWindow/CommonDefinitions.hpp
    include/startWindow/ToolButton.hpp
    include/startWindow/FramelessWindow.hpp
    include/startWindow/StartWindow.hpp
)
set(SOURCES
    src/startWindow/FramelessWindow.cpp
    src/startWindow/ToolButton.cpp
    src/startWindow/StartWindow.cpp
)

add_library(${This} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET ${This} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS true)

set_target_folder(TARGET ${This})

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
