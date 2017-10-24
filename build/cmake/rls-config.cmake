# rls CMake config file
#
# This file sets the following variables:
# rls_FOUND - Always TRUE.
# rls_INCLUDE_DIRS - Directories containing the rls include files.
# rls_IDL_DIRS - Directories containing the rls IDL files.
# rls_LIBRARIES - Libraries needed to use rls.
# rls_DEFINITIONS - Compiler flags for rls.
# rls_VERSION - The version of rls found.
# rls_VERSION_MAJOR - The major version of rls found.
# rls_VERSION_MINOR - The minor version of rls found.
# rls_VERSION_REVISION - The revision version of rls found.
# rls_VERSION_CANDIDATE - The candidate version of rls found.

message(STATUS "Found rls-1.0.0")
set(rls_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(rls_INCLUDE_DIRS
#    "/usr/local/include/rls-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(rls_IDL_DIRS
#    "/usr/local/include/rls-1/idl")
set(rls_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(rls_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(rls_LIBRARIES
        "/usr/local/components/lib/librls.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(rls_LIBRARIES
        "/usr/local/components/lib/librls.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(rls_DEFINITIONS ${<dependency>_DEFINITIONS})

set(rls_VERSION 1.0.0)
set(rls_VERSION_MAJOR 1)
set(rls_VERSION_MINOR 0)
set(rls_VERSION_REVISION 0)
set(rls_VERSION_CANDIDATE )

