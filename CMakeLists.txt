cmake_minimum_required(VERSION 3.8)
project(MainC)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        #        main/echo/echoServerMain.c
        #        main/echo/echoMultiProgress.c
        #        main/reference/echoMultiThread.c
        #        main/fileio/seek_io.c
        #        main/process/men_segments.c
        #        main/process/display_env.c
        #        main/process/t_fork.c
        #        main/process/fork_file_sharing.c
        #        main/process/t_vfork.c
        #        main/process/fork_sig_sync.c
        #        echoserver.c
        #        helper.c
        #        helper.h
        #        echo.c
        #        main/reference/echoMultiProgressCopy.c
        #        main/other/echoServerReview.c
        #        main/other/echoTreadsTest.cpp
        #        main/util/Test.cpp
        main/code/T3.c
        )
add_executable(MainC ${SOURCE_FILES})