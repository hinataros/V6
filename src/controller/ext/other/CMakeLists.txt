# @author Sho Miyahara 2018

# add_subdirectory(defaultController)
# 
set(srcs
  gainSchedule.cpp
  kineticEnergy.cpp
  forceEstimation.cpp
  rootLinkManipulability.cpp
  RNSAccelerationDistribution.cpp
  angularAccelerationDistribution.cpp
  angularVelocityDistribution.cpp
  dampingDistribution.cpp
  baseOfSupport.cpp
  constraintCheck.cpp
  systemAngularMomentumLimitation.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" other_srcs)
set(other_srcs ${other_srcs} PARENT_SCOPE)
