# @author Sho Miyahara 2018

set(srcs
  testMotionController.cpp
  relativeAngularAcceleration.cpp
  RAA_noDistribution.cpp
  RAA_fullBase.cpp
  RAA_partialBase.cpp
  RAA_RNS.cpp
  relativeAngularVelocity.cpp
  RAV_noDistribution.cpp
  RAV_fullBase.cpp
  RAV_noBase.cpp
  RAV_partialBase.cpp
  resolvedMomentumControl.cpp
  jointLimitAvoidance.cpp
  jointLimitStop.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" motionController_srcs)
set(motionController_srcs ${motionController_srcs} PARENT_SCOPE)
