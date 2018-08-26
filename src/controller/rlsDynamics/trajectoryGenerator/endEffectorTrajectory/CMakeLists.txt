# @author Sho Miyahara 2017

set(srcs
  endEffectorTrajectoryCP.cpp
  # endEffectorWalking.cpp
  # endEffectorWalkingToeoff.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" endEffectorTrajectory_srcs)
set(endEffectorTrajectory_srcs ${endEffectorTrajectory_srcs} PARENT_SCOPE)
