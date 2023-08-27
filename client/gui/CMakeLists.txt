cmake_minimum_required(VERSION 3.15)

set(This gui)

project(${This} VERSION ${MOFIP_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GUI Options
# =======================================================================
unset(GUI_BUILD_SHARED_LIBRARY CACHE)
option(GUI_BUILD_SHARED_LIBRARY "Build gui with shared library" ON)

# Variables definition
# =======================================================================
set(BUILD_TYPE STATIC)
if(GUI_BUILD_SHARED_LIBRARY)
    set(BUILD_TYPE SHARED)
    message(STATUS "Use SHARED libraries in GUI")
else()
    message(STATUS "Use STATIC libraries in GUI")
endif(GUI_BUILD_SHARED_LIBRARY)

set(INSTALL_GUI_DATA_DIR "${INSTALL_MOFIP_DIR}/data/gui/")

# Common configuration file
# =======================================================================
configure_file(guiConfig.h.in guiConfig.h)

# Qt5 package configuration
# =======================================================================
set(QT_COMPILER_DIR "c:\\Qt\\5.15.2\\msvc2019_64")
set(Qt5_DIR "${QT_COMPILER_DIR}\\lib\\cmake\\Qt5\\" CACHE PATH "Initial cache" FORCE)

# for show debug information you need create system environment variable QT_DEBUG_PLUGINS=1
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
link_libraries(Qt5::Widgets)

if(GUI_BUILD_SHARED_LIBRARY)
    set(BUILD_TYPE SHARED)
    init_library_msvc(SHARED_LIB)
else(GUI_BUILD_SHARED_LIBRARY)
    init_library_msvc()
endif(GUI_BUILD_SHARED_LIBRARY)

# Interface targets definitions
# =======================================================================
set(common_gui_target common_mofip_gui)
add_library(${common_gui_target} INTERFACE)
target_include_directories(${common_gui_target} INTERFACE
    "${PROJECT_BINARY_DIR}"
)

# Targets definitions
# =======================================================================
add_subdirectory(MofIPWidgets)
add_subdirectory(MofIPGui)
set(LIBS
    MofIPWidgets
    MofIPGui
)
# add WIN32 after target name for get debug console
add_executable(${This}
    main.cpp
)
target_include_directories(${This}
    PUBLIC
        ${LIBS}
)
target_link_libraries(${This}
    PRIVATE
        ${LIBS}
        ${common_gui_target}
)

# Configure build directories for GUI
# =======================================================================
set_target_folder(TARGET ${This})

foreach(lib_item ${LIBS})
    message(STATUS "Configure folders for target: ${lib_item}")
    if(GUI_BUILD_SHARED_LIBRARY)
        set_target_folder(TARGET ${lib_item} NAME_DIR ${This})
        copy_dll_from_shared_to_exe_target(SHARED_TARGET ${lib_item} EXECUTE_TARGET ${This})
    else(GUI_BUILD_SHARED_LIBRARY)
        set_target_folder(TARGET ${lib_item})
    endif(GUI_BUILD_SHARED_LIBRARY)
endforeach(lib_item ${LIBS})

# INSTALL GUI part
# =======================================================================
install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
install(FILES
		${QT_COMPILER_DIR}/bin/Qt5Cored.dll
		${QT_COMPILER_DIR}/bin/Qt5Guid.dll
		${QT_COMPILER_DIR}/bin/Qt5Widgetsd.dll
	DESTINATION
		${INSTALL_MOFIP_DIR}
)
install(DIRECTORY
		${QT_COMPILER_DIR}/plugins/platforms
	DESTINATION
		${INSTALL_MOFIP_DIR}
)
install(DIRECTORY
		${CMAKE_CURRENT_SOURCE_DIR}/data/
	DESTINATION
		${INSTALL_GUI_DATA_DIR}
)
