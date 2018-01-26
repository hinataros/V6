# @author Sho Miyahara 2017

set(srcs
  ddthD.cpp
  ddqD.cpp
  workAcceleration.cpp
  baseAccelerationSynergy.cpp
  mixedAccelerationSynergy.cpp
  centroidalAccelerationSynergy.cpp
  noname.cpp
  baseGeneralizedMomentum.cpp
  mixedGeneralizedMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationController_srcs)
set(accelerationController_srcs ${accelerationController_srcs} PARENT_SCOPE)
