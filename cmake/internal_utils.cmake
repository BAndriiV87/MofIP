
# Set project folders for target. Set compilation result directories for each target
function(set_target_folder)
    set(oneValueArgs TARGET NAME_DIR)
    cmake_parse_arguments(LOCAL_OPTIONS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(target ${LOCAL_OPTIONS_TARGET})

    if(LOCAL_OPTIONS_NAME_DIR)
        set(dir_name ${LOCAL_OPTIONS_NAME_DIR})
    else(LOCAL_OPTIONS_NAME_DIR)
        set(dir_name ${target})
    endif(LOCAL_OPTIONS_NAME_DIR)
    
    get_target_property(targetType ${target} TYPE)

    set(outputDirectory lib)
    set(targetFolder)
    if(${targetType} STREQUAL "STATIC_LIBRARY")
        set(targetFolder StaticLibraries)
    endif(${targetType} STREQUAL "STATIC_LIBRARY")

    if(${targetType} STREQUAL "SHARED_LIBRARY")
        set(targetFolder SharedLibraries)
    endif(${targetType} STREQUAL "SHARED_LIBRARY")

    if(${targetType} STREQUAL "EXECUTABLE")
        set(targetFolder Executables)
        set(outputDirectory bin)
    endif(${targetType} STREQUAL "EXECUTABLE")

    if(${targetType} STREQUAL "INTERFACE_LIBRARY")
        set(targetFolder InterfaceLibraries)
    endif(${targetType} STREQUAL "INTERFACE_LIBRARY")

    if(targetFolder)
        set(rootOuputDirectory "${CMAKE_BINARY_DIR}/out")
        set(libOutputDirectory "${rootOuputDirectory}/lib")
        set(binOutputDirectory "${rootOuputDirectory}/bin")

        set_target_properties(${target} PROPERTIES
            FOLDER ${targetFolder}
            RUNTIME_OUTPUT_DIRECTORY "${binOutputDirectory}"
            LIBRARY_OUTPUT_DIRECTORY "${libOutputDirectory}"
            ARCHIVE_OUTPUT_DIRECTORY "${libOutputDirectory}"
            PDB_OUTPUT_DIRECTORY "${binOutputDirectory}"
            COMPILE_PDB_OUTPUT_DIRECTORY "${libOutputDirectory}")

        set_target_properties(${target}
            PROPERTIES
            PDB_NAME "${dir_name}"
            PDB_NAME_DEBUG "${dir_name}"
            COMPILE_PDB_NAME "${dir_name}"
            COMPILE_PDB_NAME_DEBUG "${dir_name}")

        message(STATUS "Set folder for target <${target}> is <${targetFolder}>")
    endif(targetFolder)

endfunction(set_target_folder)

# This function copy target ouput shared library to directory of executable target out directory 
function(copy_dll_from_shared_to_exe_target)
    set(oneValueArgs SHARED_TARGET EXECUTE_TARGET)
    cmake_parse_arguments(LOCAL_OPTIONS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    get_target_property(shared_target_dir ${LOCAL_OPTIONS_SHARED_TARGET} RUNTIME_OUTPUT_DIRECTORY)
    get_target_property(execute_target_dir ${LOCAL_OPTIONS_EXECUTE_TARGET} RUNTIME_OUTPUT_DIRECTORY)

    if(shared_target_dir AND execute_target_dir)
        add_custom_command(
            TARGET ${LOCAL_OPTIONS_EXECUTE_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    "${shared_target_dir}\\$<CONFIG>\\${LOCAL_OPTIONS_SHARED_TARGET}.dll"
                    "${execute_target_dir}\\$<CONFIG>\\"
        )
    endif(shared_target_dir AND execute_target_dir)
endfunction(copy_dll_from_shared_to_exe_target)

function(set_library_type_msvc)
    set(options SHARED_LIB)
    cmake_parse_arguments(LOCAL_OPTIONS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(MSVC)
        if(LOCAL_OPTIONS_SHARED_LIB)
            set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE CACHE BOOL "" FORCE)
            set(BUILD_SHARED_LIBS TRUE CACHE BOOL "" FORCE)
        else(LOCAL_OPTIONS_SHARED_LIB)
            set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF CACHE BOOL "" FORCE)
            set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        endif(LOCAL_OPTIONS_SHARED_LIB)
    endif()

endfunction(set_library_type_msvc)
