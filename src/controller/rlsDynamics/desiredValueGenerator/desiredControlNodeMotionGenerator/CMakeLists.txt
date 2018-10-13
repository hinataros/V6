# @author Sho Miyahara 2018

set(srcs
  desiredControlNodeMotionGeneratorCP.cpp
  desiredControlNodeMotionGeneratorCPabs.cpp
  desiredControlNodeMotionGeneratorWalking.cpp
  # controlNodeMotionWalkingToeoff.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredControlNodeMotionGenerator_srcs)
set(desiredControlNodeMotionGenerator_srcs ${desiredControlNodeMotionGenerator_srcs} PARENT_SCOPE)
