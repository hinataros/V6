# @author Sho Miyahara 2017

set(srcs
  zeroMomentum.cpp
  linearMomentum.cpp
  centroidalAngularMomentum.cpp
  dcmMomentum.cpp
  baseAngularMomentum.cpp
  baseMomentum.cpp
  centroidalMomentum.cpp
  centroidalDcmMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" momentumController_srcs)
set(momentumController_srcs ${momentumController_srcs} PARENT_SCOPE)
