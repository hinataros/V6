# @author Sho Miyahara 2017

set(srcs
  externalWrenchTrajectoryCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" externalWrenchTrajectory_srcs)
set(externalWrenchTrajectory_srcs ${externalWrenchTrajectory_srcs} PARENT_SCOPE)
