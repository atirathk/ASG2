# CMakeList.txt : CMake project for ASG2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

PROJECT(ASG2)
set (CMAKE_CXX_STANDARD 17)

set (ASG2_SOURCES
    commands.cpp    commands.h
    file_sys.cpp	file_sys.h
    debug.cpp		debug.h
    util.cpp		util.h
)

set (MAIN_SOURCES
    ${ASG2_SOURCES}
    testClient.cpp
)

ADD_EXECUTABLE(yshell ${MAIN_SOURCES})
add_custom_target(run
    DEPENDS yshell
    COMMAND ./yshell)
#main.cpp
# TODO: Add tests and install targets if needed.
