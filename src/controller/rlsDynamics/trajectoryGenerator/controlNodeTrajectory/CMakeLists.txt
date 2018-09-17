# @author Sho Miyahara 2017

set(srcs
  controlNodeTrajectoryCP.cpp
  controlNodeTrajectoryWalking.cpp
  # controlNodeWalkingToeoff.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeTrajectory_srcs)
set(controlNodeTrajectory_srcs ${controlNodeTrajectory_srcs} PARENT_SCOPE)
