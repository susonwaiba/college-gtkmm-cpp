cmake_minimum_required(VERSION 2.8.7)
project(Chat)

if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

add_subdirectory(opt)

add_executable(Chat
        main.cpp

        include/Config.cpp

        windows/Main.cpp
        windows/Login.cpp
        windows/Register.cpp
        windows/Home.cpp
        windows/About.cpp
        windows/AddFriend.cpp

#        example/ScrollWindow.cpp

        )


#opt/cpr library
target_link_libraries(Chat ${CPR_LIBRARIES})
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#Required
find_package(PkgConfig REQUIRED)
#GTKMM
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})
target_link_libraries(Chat ${GTKMM_LIBRARIES})
#GTK3
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})
#add_definitions(${GTK3_CFLAGS_OTHER})
#target_link_libraries(Chat ${GTK3_LIBRARIES})