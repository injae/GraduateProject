#[[
@file   CMakeLists.txt
@brief  the cmake file for source files that are given to build a library gpcrypt        
@date   Sep. 1, 2020
@author Myungsun Kim

        This CMakeLists.txt file is customized to build a sample code for supporting the graduate project.
        For the other purpose of use, you need to modify the file properly.
]]

# list header and source files
#
set(HEADER_LIST "../include/crypt.h"
                # some your header files
                )
set(SRC_LIST "./crypt.cc"
             # some your source files
             )

# Create a static library called "gpcrypt" which includes the source file "crypt.cc".
# If you have any other files, add to below them
add_library (gpcrypt STATIC ${SRC_LIST} ${HEADER_LIST})

# Make sure the compiler can find include files for our gpcrypt library
# when other libraries or executables link to gpcrypt
#target_compile_options(gpcrypt PRIVATE -std=c++11 -O3)
target_include_directories (gpcrypt PUBLIC ../include)