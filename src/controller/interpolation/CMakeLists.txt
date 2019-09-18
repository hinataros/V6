# @author Sho Miyahara 2017

set(srcs
  spline3.cpp
  spline5.cpp
  unitQuaternionFix.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" interpolation_srcs)
set(interpolation_srcs ${interpolation_srcs} PARENT_SCOPE)
