cmake_minimum_required(VERSION 3.15)

set(this serverMoFip)

project(${this} VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

add_executable(${this} main.cpp)
