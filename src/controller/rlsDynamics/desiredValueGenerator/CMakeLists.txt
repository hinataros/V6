# @author Sho Miyahara 2018

add_subdirectory(initialize)
add_subdirectory(desiredBaseTranslationGenerator)
add_subdirectory(desiredBaseOrientationGenerator)
add_subdirectory(desiredControlNodeMotionGenerator)
add_subdirectory(desiredControlNodeForceGenerator)
add_subdirectory(desiredComGenerator)
add_subdirectory(desiredDcmGenerator)
add_subdirectory(desiredExternalWrenchGenerator)
add_subdirectory(desiredZeroGenerator)
add_subdirectory(desiredValueGenerator)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredValueGenerator_srcs)

set(desiredValueGenerator_srcs
  ${initialize_srcs}
  ${desiredBaseTranslationGenerator_srcs}
  ${desiredBaseOrientationGenerator_srcs}
  ${desiredControlNodeMotionGenerator_srcs}
  ${desiredControlNodeForceGenerator_srcs}
  ${desiredComGenerator_srcs}
  ${desiredDcmGenerator_srcs}
  ${desiredExternalWrenchGenerator_srcs}
  ${desiredZeroGenerator_srcs}
  ${desiredValueGenerator_srcs}
  PARENT_SCOPE
  )
