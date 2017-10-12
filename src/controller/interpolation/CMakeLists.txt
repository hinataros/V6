set(srcs
  spline5.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" interpolation_srcs)
set(interpolation_srcs ${interpolation_srcs} PARENT_SCOPE)
