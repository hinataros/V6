file(GLOB sources *.cpp)
file(GLOB headers *.hpp)

add_definitions(-fPIC)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# add_subdirectory(src)

add_library(convexsolver STATIC ${sources} ${headers})
