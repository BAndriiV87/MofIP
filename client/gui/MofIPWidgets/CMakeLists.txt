cmake_minimum_required(VERSION 3.16)

set(This MofIPWidgets)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set_library_type_msvc(SHARED_LIB)

set(HEADERS
    include/MofIPWidgets.hpp
    include/MofIPWidgets/MofIPPushButton.hpp
    include/MofIPWidgets/MofipWidgetsCommon.hpp
    include/MofIPWidgets/MofIPWidgetsFactory.hpp
)
set(SOURCES
    src/MofIPPushButton.cpp
    src/MofipWidgetsCommon.cpp
    src/MofIPWidgetsFactory.cpp
)

add_library(${This} SHARED ${HEADERS} ${SOURCES})
target_include_directories(${This} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET ${This} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS true)

set_target_folder(TARGET ${This})

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
