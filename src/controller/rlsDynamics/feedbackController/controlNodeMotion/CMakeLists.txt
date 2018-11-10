# @author Sho Miyahara 2018

set(srcs
  controlNodeMotionPI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeMotion_srcs)
set(controlNodeMotion_srcs ${controlNodeMotion_srcs} PARENT_SCOPE)
