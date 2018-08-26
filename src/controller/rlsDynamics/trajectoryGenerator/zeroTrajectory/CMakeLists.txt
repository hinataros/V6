# @author Sho Miyahara 2017

set(srcs
  baseTranslationZeroTrajectory.cpp
  baseOrientationZeroTrajectory.cpp
  endEffectorZeroTrajectory.cpp
  comZeroTrajectory.cpp
  dcmZeroTrajectory.cpp
  externalWrenchZeroTrajectory.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" zeroTrajectory_srcs)
set(zeroTrajectory_srcs ${zeroTrajectory_srcs} PARENT_SCOPE)
