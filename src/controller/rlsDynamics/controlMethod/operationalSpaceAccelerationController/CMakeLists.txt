# @author Sho Miyahara 2018

set(srcs
  decomposeEndEffectorAcceleration.cpp
  relativeAccelerationBaseMap.cpp
  relativeAccelerationMixedMap.cpp
  relativeAccelerationCentroidalMap.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" operationalSpaceAccelerationController_srcs)
set(operationalSpaceAccelerationController_srcs ${operationalSpaceAccelerationController_srcs} PARENT_SCOPE )
