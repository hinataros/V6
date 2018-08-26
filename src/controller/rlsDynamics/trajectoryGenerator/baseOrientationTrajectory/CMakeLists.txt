# @author Sho Miyahara 2017

set(srcs
  baseOrientationTrajectoryCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseOrientationTrajectory_srcs)
set(baseOrientationTrajectory_srcs ${baseOrientationTrajectory_srcs} PARENT_SCOPE)
