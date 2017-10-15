cmake_minimum_required(VERSION 3.8)
project(MainC)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        #        echoserver.c
        #        helper.c
        #        helper.h
        #        echo.c
        main/echo/echoServerMain.c
        main/reference/echoMultiProgressCopy.c
        main/echo/echoMultiProgress.c
        main/echo/echoServerReview.c
        main/reference/echoMultiThread.c
        main/echo/echoTreadsTest.cpp
        #        main/util/Test.cpp
        )
add_executable(MainC ${SOURCE_FILES})