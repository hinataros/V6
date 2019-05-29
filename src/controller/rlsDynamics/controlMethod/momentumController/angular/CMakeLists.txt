# @author Sho Miyahara 2018

set(srcs
  centroidalAngularMomentum.cpp
  baseAngularMomentum.cpp
  reactionNullSpaceMomentum.cpp
  centroidalAngularMomentumDamping.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" angular_srcs)
set(angular_srcs ${angular_srcs} PARENT_SCOPE)
