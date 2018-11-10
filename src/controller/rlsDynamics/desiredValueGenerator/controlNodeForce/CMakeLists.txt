# @author Sho Miyahara 2018

set(srcs
  controlNodeForceCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeForce_srcs)
set(controlNodeForce_srcs ${controlNodeForce_srcs} PARENT_SCOPE)
