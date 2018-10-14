# @author Sho Miyahara 2018

set(srcs
  testInverseDynamicsController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" inverseDynamicsController_srcs)
set(inverseDynamicsController_srcs ${inverseDynamicsController_srcs} PARENT_SCOPE)
