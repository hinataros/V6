# @author Sho Miyahara 2017

add_subdirectory(desiredBaseTranslationGenerator)
add_subdirectory(desiredBaseOrientationGenerator)
add_subdirectory(desiredControlNodeAccelerationGenerator)
add_subdirectory(desiredControlNodeWrenchGenerator)
add_subdirectory(desiredComGenerator)
add_subdirectory(desiredDcmGenerator)
add_subdirectory(desiredExternalWrenchGenerator)
add_subdirectory(desiredZeroGenerator)

set(srcs
  desiredValueGenerator.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredValueGenerator_srcs)
set(desiredValueGenerator_srcs
  ${desiredBaseTranslationGenerator_srcs}
  ${desiredBaseOrientationGenerator_srcs}
  ${desiredControlNodeAccelerationGenerator_srcs}
  ${desiredControlNodeWrenchGenerator_srcs}
  ${desiredComGenerator_srcs}
  ${desiredDcmGenerator_srcs}
  ${desiredExternalWrenchGenerator_srcs}
  ${desiredZeroGenerator_srcs}
  ${desiredValueGenerator_srcs}
  PARENT_SCOPE
  )
