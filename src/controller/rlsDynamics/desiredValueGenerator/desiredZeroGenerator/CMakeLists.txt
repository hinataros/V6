# @author Sho Miyahara 2017

set(srcs
  desiredBaseTranslationZeroGenerator.cpp
  desiredBaseOrientationZeroGenerator.cpp
  desiredControlNodeAccelerationZeroGenerator.cpp
  desiredControlNodeWrenchZeroGenerator.cpp
  desiredComZeroGenerator.cpp
  desiredDcmZeroGenerator.cpp
  desiredExternalWrenchZeroGenerator.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredZeroGenerator_srcs)
set(desiredZeroGenerator_srcs ${desiredZeroGenerator_srcs} PARENT_SCOPE)
