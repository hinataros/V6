# @author Sho Miyahara 2018

set(srcs
  desiredControlNodeForceGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredControlNodeForceGenerator_srcs)
set(desiredControlNodeForceGenerator_srcs ${desiredControlNodeForceGenerator_srcs} PARENT_SCOPE)
