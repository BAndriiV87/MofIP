cmake_minimum_required(VERSION 3.16)

set(This gui)

project(${This} VERSION ${MOFIP_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

unset(GUI_BUILD_SHARED_LIBRARY CACHE)
option(GUI_BUILD_SHARED_LIBRARY "Build gui with shared library" ON)

set(QT_COMPILER_DIR "c:\\Qt\\5.15.2\\msvc2019_64")
set(Qt5_DIR "${QT_COMPILER_DIR}\\lib\\cmake\\Qt5\\" CACHE PATH "Initial cache" FORCE)

# Create environment variable QT_DEBUG_PLUGINS=1 for show debug information
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_subdirectory(MofIPWidgets)

add_executable(${This}
    main.cpp
)
target_include_directories(${This} PUBLIC MofIPWidgets)
target_link_libraries(${This} 
PRIVATE 
Qt5::Widgets
MofIPWidgets
)

set_target_folder(TARGET ${This})
if(GUI_BUILD_SHARED_LIBRARY)
    set_target_folder(TARGET MofIPWidgets NAME_DIR ${This})
    copy_dll_from_shared_to_exe_target(SHARED_TARGET MofIPWidgets EXECUTE_TARGET ${This})
else(GUI_BUILD_SHARED_LIBRARY)
    set_target_folder(TARGET MofIPWidgets)
endif(GUI_BUILD_SHARED_LIBRARY)

# Copy dlls to output directory of target <gui> for launch QT executable
get_target_property(${This}_runtime_out_dir ${This} RUNTIME_OUTPUT_DIRECTORY)
add_custom_command(
    TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${QT_COMPILER_DIR}\\bin\\Qt5Cored.dll
            ${QT_COMPILER_DIR}\\bin\\Qt5Guid.dll
            ${QT_COMPILER_DIR}\\bin\\Qt5Widgetsd.dll
            ${${This}_runtime_out_dir}\\$<CONFIG>\\
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${QT_COMPILER_DIR}\\plugins\\platforms\\" 
            "${${This}_runtime_out_dir}\\$<CONFIG>\\platforms\\"
)
