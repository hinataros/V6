# @author Sho Miyahara 2017

set(srcs
  fullDynamicsController.cpp
  momentumInverseDynamicsController.cpp
  highGainController.cpp
  spatialDynamicsSolver.cpp
  dlrSolver.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" inverseDynamicsController_srcs)
set(inverseDynamicsController_srcs ${inverseDynamicsController_srcs} PARENT_SCOPE)
