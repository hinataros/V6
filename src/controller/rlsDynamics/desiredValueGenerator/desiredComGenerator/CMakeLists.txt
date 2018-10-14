# @author Sho Miyahara 2018

set(srcs
  desiredComGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredComGenerator_srcs)
set(desiredComGenerator_srcs ${desiredComGenerator_srcs} PARENT_SCOPE)
