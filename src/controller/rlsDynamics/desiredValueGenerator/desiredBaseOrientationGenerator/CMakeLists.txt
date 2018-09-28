# @author Sho Miyahara 2017

set(srcs
  desiredBaseOrientationGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredBaseOrientationGenerator_srcs)
set(desiredBaseOrientationGenerator_srcs ${desiredBaseOrientationGenerator_srcs} PARENT_SCOPE)
