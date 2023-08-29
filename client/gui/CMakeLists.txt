cmake_minimum_required(VERSION 3.16)

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
endif(GUI_BUILD_SHARED_LIBRARY)

set(INSTALL_MOFIP_DIR ${CMAKE_INSTALL_PREFIX})
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

# Targets definitions
# =======================================================================
add_subdirectory(MofIPWidgets)
add_subdirectory(MofIPGui)
set(LIBS
    MofIPWidgets
    MofIPGui
)

# Main executable target
# =======================================================================
# add WIN32 after target name for get debug console
add_executable(${This} main.cpp)
set_target_properties(${This} PROPERTIES 
	VS_DEBUGGER_ENVIRONMENT 
		"PATH=c:/Qt/5.15.2/msvc2019_64/bin;c:/Qt/5.15.2/msvc2019_64/plugins/platforms"
)
target_include_directories(${This}
    PUBLIC
        ${LIBS}
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${This}
    PRIVATE
        ${LIBS}
)
set_target_folder(TARGET ${This})

# Configure build directories for GUI
# =======================================================================

foreach(lib_item ${LIBS})
    message(STATUS "Configure folders for target: ${lib_item}")
    set_target_folder(TARGET ${lib_item})
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

