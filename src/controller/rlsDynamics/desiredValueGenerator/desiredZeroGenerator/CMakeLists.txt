# @author Sho Miyahara 2018

set(srcs
  desiredBaseTranslationZeroGenerator.cpp
  desiredBaseOrientationZeroGenerator.cpp
  desiredControlNodeMotionZeroGenerator.cpp
  desiredControlNodeForceZeroGenerator.cpp
  desiredComZeroGenerator.cpp
  desiredDcmZeroGenerator.cpp
  desiredExternalWrenchZeroGenerator.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredZeroGenerator_srcs)
set(desiredZeroGenerator_srcs ${desiredZeroGenerator_srcs} PARENT_SCOPE)
