# @author Sho Miyahara 2018

set(srcs
  relativeVelocityBaseMap.cpp
  relativeVelocityMixedMap.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" operationalSpaceVelocityController_srcs)
set(operationalSpaceVelocityController_srcs ${operationalSpaceVelocityController_srcs} PARENT_SCOPE)
