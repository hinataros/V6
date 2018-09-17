# @author Sho Miyahara 2017

add_subdirectory(baseTranslationTrajectory)
add_subdirectory(baseOrientationTrajectory)
add_subdirectory(controlNodeTrajectory)
add_subdirectory(comTrajectory)
add_subdirectory(dcmTrajectory)
add_subdirectory(externalWrenchTrajectory)
add_subdirectory(zeroTrajectory)

set(srcs
  trajectoryGenerator.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" trajectoryGenerator_srcs)
set(trajectoryGenerator_srcs
  ${baseTranslationTrajectory_srcs}
  ${baseOrientationTrajectory_srcs}
  ${controlNodeTrajectory_srcs}
  ${comTrajectory_srcs}
  ${dcmTrajectory_srcs}
  ${externalWrenchTrajectory_srcs}
  ${zeroTrajectory_srcs}
  ${trajectoryGenerator_srcs}
  PARENT_SCOPE
  )
