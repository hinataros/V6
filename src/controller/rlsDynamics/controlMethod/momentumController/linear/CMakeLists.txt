# @author Sho Miyahara 2018

set(srcs
  linearMomentum.cpp
  vrpMomentum.cpp
  vrpZcomMomentum.cpp
  vrpMomentumwXt.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" linear_srcs)
set(linear_srcs ${linear_srcs} PARENT_SCOPE)
