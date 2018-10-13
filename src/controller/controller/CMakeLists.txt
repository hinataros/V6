# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  finalize.cpp
  makeRlsDynamics.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controller_srcs)
set(controller_srcs ${controller_srcs} PARENT_SCOPE)
