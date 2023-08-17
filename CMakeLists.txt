cmake_minimum_required(VERSION 3.15)

set(This MofIP)
project(${This})
set(MOFIP_VERSION 0.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/internal_utils.cmake)

init_library_msvc()

# Organize applications, libraries, etc. in folders in the IDE.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

get_directory_property(ParenDirectory PARENT_DIRECTORY)
if(ParenDirectory STREQUAL "")

	# Keep Google Test's linkage of the runtime in sync with our own.
	if(RUNTIME_STATIC_LINKAGE)
        set(gtest_force_shared_crt OFF CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is build as static lib." FORCE)
    else(RUNTIME_STATIC_LINKAGE)
        set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is build as static lib." FORCE)
    endif(RUNTIME_STATIC_LINKAGE)

	# Google Test
	set(BUILD_GTEST ON CACHE BOOL "Builds the googletest subproject" FORCE)
	set(BUILD_GMOCK OFF CACHE BOOL "Builds the googlemock subproject" FORCE)
	add_subdirectory(external/googletest)
	set_target_folder(TARGET gtest_main)
	set_target_folder(TARGET gtest)

    # Application Libraries
	add_subdirectory(libs)

    # Application Runtimes part
    if(MSVC)
        # Suppress Microsoft warnings about functions being unsafe
        add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
        add_subdirectory(client)
    elseif(UNIX)
        add_subdirectory(server)
    else()
        message(FATAL_ERROR "The Platform incorrect. MofIP support only Windows and Unix")
    endif()

endif(ParenDirectory STREQUAL "")
