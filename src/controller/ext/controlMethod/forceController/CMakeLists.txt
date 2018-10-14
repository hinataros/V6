# @author Sho Miyahara 2018

set(srcs
  testForceController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" forceController_srcs)
set(forceController_srcs ${forceController_srcs} PARENT_SCOPE)
