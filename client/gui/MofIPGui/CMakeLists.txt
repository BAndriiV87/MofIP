cmake_minimum_required(VERSION 3.16)

set(This MofIPGui)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set_library_type_msvc(SHARED_LIB)

set(HEADERS
    include/MofIPGui.hpp
    include/MofIPGui/MainWindow.hpp
)
set(SOURCES
    src/MainWindow.cpp
)

add_library(${This} SHARED ${HEADERS} ${SOURCES})
set_property(TARGET ${This} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS true)
target_link_libraries(${This} 
    PRIVATE 
        MofIPWidgets
)
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_folder(TARGET ${This})

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
