cmake_minimum_required(VERSION 3.15)

project(MofIP VERSION 0.0.0)

IF (WIN32)
  # set stuff for windows
  add_subdirectory(client)
ELSEIF(UNIX)
  # set stuff for other systems
  add_subdirectory(server)
ENDIF()
