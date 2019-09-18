# @author Sho Miyahara 2018

set(srcs
  controlNodeRotationCP.cpp
  controlNodeRotationCPabs.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeRotation_srcs)
set(controlNodeRotation_srcs ${controlNodeRotation_srcs} PARENT_SCOPE)
