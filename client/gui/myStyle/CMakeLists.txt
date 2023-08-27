cmake_minimum_required(VERSION 3.16)

set(This myStyle)
project(${This} VERSION ${MOFIP_VERSION} LANGUAGES CXX)

set(HEADERS
    include/${This}/${This}.h
)
set(SOURCES
    src/${This}.cpp
)

set(RESOURCES
    include/myStyle/styles.qrc
)

add_library(${This} ${BUILD_TYPE} ${HEADERS} ${SOURCES} )
target_include_directories(${This} 
    PUBLIC 
        include
)

install(TARGETS ${This} DESTINATION ${INSTALL_MOFIP_DIR})
