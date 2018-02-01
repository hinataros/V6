# @author Sho Miyahara 2017

set(srcs
  baseDistribution.cpp
  centroidalDistribution.cpp
  centroidalDcmDistribution.cpp
  distributionSolver.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" forceController_srcs)
set(forceController_srcs ${forceController_srcs} PARENT_SCOPE )
