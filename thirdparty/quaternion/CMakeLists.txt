# @author Sho Miyahara 2018

project(quaternion CXX)

add_definitions(-fPIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)

add_library(quaternion STATIC ${library_sources})
