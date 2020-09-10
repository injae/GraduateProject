#[[
@file   CMakeLists.txt
@brief  the root cmake file
@date   Sep. 1, 2020
@author Myungsun Kim

        This CMakeLists.txt file is customized to build a sample code for supporting the graduate project.
        For the other purpose of use, you need to modify the file properly.
]]

cmake_minimum_required (VERSION 3.1)
project (gp2020fall
         VERSION 0.0.1
         DESCRIPTION "a sample code for helping graduate project"
         # I am only considering C++ language in this implemetation
         LANGUAGES CXX)    

# compile options
# for debig mode
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O3")
# for release mode
#set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 ${CMAKE_CXX_FLAGS}")

# openssl options
# the below folder structures are only for me
# so, after checking or installing openssl's home directory, properly alter the correspondings
find_path(
    OPENSSL_INCLUDE_DIR openssl/ec.h
    NAMES openssl/sha.h openssl/bn.h
    PATH_SUFFIXES include
    PATHS
    /usr/local/Cellar/openssl@1.1/1.1.1g/           # if necessary, append your openssl path
    NO_DEFAULT_PATH
)
find_library(
    OPENSSL_LIBRARY libcrypto.a
    PATH_SUFFIXES lib
    PATHS
    /usr/local/Cellar/openssl@1.1/1.1.1g/           # if necessary, append your openssl path
    NO_DEFAULT_PATH
)

find_package(OPENSSL REQUIRED)
if(OPENSSL_FOUND)
    message (STATUS "::OpenSSL Include directories: " ${OPENSSL_INCLUDE_DIR})
    include_directories(${OPENSSL_INCLUDE_DIR})
else()
    message (OPENSSL_ERROR "::OpenSSL Not found :-(")
endif()

# the project's entire directory structure.
add_subdirectory (src)
add_subdirectory (tests)