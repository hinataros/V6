#@author Sho Miyahara 2017

set(srcs
  zeroMotion.cpp
  zeroMomentum.cpp
  zeroDistribution.cpp
  zeroTorque.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" zeroController_srcs)
set(zeroController_srcs ${zeroController_srcs} PARENT_SCOPE)
