cmake_minimum_required(VERSION 3.8)
project(MainC)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        echoserver.c
#        helper.c
#        helper.h
#        echo.c
        echoServerMain.c
        )
add_executable(MainC ${SOURCE_FILES})