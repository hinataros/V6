# @author Sho Miyahara 2017

set(srcs
  comTrajectoryCP.cpp
  )
MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" comTrajectory_srcs)
set(comTrajectory_srcs ${comTrajectory_srcs} PARENT_SCOPE)
