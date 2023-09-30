cmake_minimum_required(VERSION 3.16)

set(This gui)

project(${This} VERSION ${MOFIP_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Variables definition
# -----------------------------------------------
set(INSTALL_MOFIP_DIR ${CMAKE_INSTALL_PREFIX})
set(INSTALL_GUI_DATA_DIR "${INSTALL_MOFIP_DIR}/data/gui/")

configure_file(guiConfig.h.in guiConfig.h)

# Qt5 package configuration
# -----------------------------------------------
set(QT_COMPILER_DIR "c:\\Qt\\5.15.2\\msvc2019_64")
set(Qt5_DIR "${QT_COMPILER_DIR}\\lib\\cmake\\Qt5\\" CACHE PATH "Initial cache" FORCE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Concurrent Widgets)
link_libraries(Qt5::Core Qt5::Concurrent Qt5::Widgets)

# GUI targets
# -----------------------------------------------
add_subdirectory(mofipwidgets)
#add_subdirectory(tempgui)

# Main executable target
# -----------------------------------------------
add_executable(${This} main.cpp) # add WIN32 after target name for get debug in console
set_target_properties(${This} PROPERTIES 
	VS_DEBUGGER_ENVIRONMENT 
		"PATH=c:/Qt/5.15.2/msvc2019_64/bin;c:/Qt/5.15.2/msvc2019_64/plugins/platforms"
)
target_include_directories(${This}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${This}
    PRIVATE
        mofipwidgets
        #tempgui
)
set_target_folder(TARGET ${This})

# INSTALL GUI rulls
# -----------------------------------------------
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
