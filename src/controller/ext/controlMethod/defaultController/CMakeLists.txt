# @author Sho Miyahara 2018

set(srcs
  defaultController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" defaultController_srcs)
set(defaultController_srcs ${defaultController_srcs} PARENT_SCOPE)
