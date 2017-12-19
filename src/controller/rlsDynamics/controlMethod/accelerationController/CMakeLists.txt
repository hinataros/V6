set(srcs
  ddthD.cpp
  ddqD.cpp
  baseAccelerationSynergy.cpp
  mixedAccelerationSynergy.cpp
  centroidalAccelerationSynergy.cpp
  noname.cpp
  baseGeneralizedMomentum.cpp
  mixedGeneralizedMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationController_srcs)
set(accelerationController_srcs ${accelerationController_srcs} PARENT_SCOPE)
