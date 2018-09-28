# @author Sho Miyahara 2017

set(srcs
  desiredControlNodeAccelerationGeneratorCP.cpp
  desiredControlNodeAccelerationGeneratorCPabs.cpp
  desiredControlNodeAccelerationGeneratorWalking.cpp
  # controlNodeAccelerationWalkingToeoff.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredControlNodeAccelerationGenerator_srcs)
set(desiredControlNodeAccelerationGenerator_srcs ${desiredControlNodeAccelerationGenerator_srcs} PARENT_SCOPE)
