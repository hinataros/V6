# cmake_minimum_required(VERSION 3.0)

project(cfsqp)

# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

# @rewrite Akinori Miyata 2018

add_definitions(-fPIC)

file(GLOB sources *.cpp)
file(GLOB headers *.hpp)
set(library_sources ${sources})
# list(REMOVE_ITEM library_sources ${CMAKE_CURRENT_SOURCE_DIR}/qptest.cpp)

add_definitions(-fPIC)

add_library(cfsqp STATIC ${library_sources} ${headers})
