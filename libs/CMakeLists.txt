if(MSVC)
    # Suppress Microsoft warnings about functions being unsafe
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
endif(MSVC)

add_subdirectory(temp)
set_target_folder(TARGET temp)
