# @author Sho Miyahara 2017

set(srcs
  ddthD.cpp
  ddqthD.cpp
  ddqthinit.cpp
  workAcceleration.cpp
  baseAccelerationSynergy.cpp
  mixedAccelerationSynergy.cpp
  centroidalAccelerationSynergy.cpp
  rest_cmlC.cpp
  rest_clCm.cpp
  baseGeneralizedMomentum.cpp
  mixedGeneralizedMomentum.cpp
  accelerationSolver.cpp
  hinata.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationController_srcs)
set(accelerationController_srcs ${accelerationController_srcs} PARENT_SCOPE)
