# @author Sho Miyahara 2018

set(srcs
  linearMomentum.cpp
  centroidalAngularMomentum.cpp
  dcmMomentum.cpp
  baseAngularMomentum.cpp
  baseMomentum.cpp
  baseDcmMomentum.cpp
  centroidalMomentum.cpp
  centroidalDcmMomentum.cpp
  centroidalCmpMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" momentumController_srcs)
set(momentumController_srcs ${momentumController_srcs} PARENT_SCOPE)
