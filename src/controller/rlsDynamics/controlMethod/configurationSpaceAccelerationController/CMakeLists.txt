# @author Sho Miyahara 2018

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
  rcamd.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" configurationSpaceAccelerationController_srcs)
set(configurationSpaceAccelerationController_srcs ${configurationSpaceAccelerationController_srcs} PARENT_SCOPE)
