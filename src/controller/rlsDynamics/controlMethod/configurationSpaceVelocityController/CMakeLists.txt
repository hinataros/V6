# @author Sho Miyahara 2018

set(srcs
  baseVelocitySynergy.cpp
  mixedVelocitySynergy.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" configurationSpaceVelocityController_srcs)
set(configurationSpaceVelocityController_srcs ${configurationSpaceVelocityController_srcs} PARENT_SCOPE)
