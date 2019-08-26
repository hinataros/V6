# @author Sho Miyahara 2018

set(srcs
  readController.cpp
  allReadController.cpp
  readParameter.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readController_srcs)
set(readController_srcs ${readController_srcs} PARENT_SCOPE)
