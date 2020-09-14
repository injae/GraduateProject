#[[
@file   CMakeLists.txt
@brief  the cmake file for the main entry       
@date   Sep. 1, 2020
@author Myungsun Kim

        This CMakeLists.txt file is customized to build a sample test code for supporting the graduate project.
        For the other purpose of use, you need to modify the file properly.
]]

# Add executable called "test" that is built from the source file(s)
# "test.cc" and some others, if any 
add_executable (test test.cc)

# Link the executable to the gbcrypt library. 
# Since the  library has public include directories we will use those link directories when building this executable binary
target_compile_options(test PUBLIC -std=c++11 -O3)
target_link_libraries (test LINK_PUBLIC gpcrypt ${OPENSSL_LIBRARY})