# @author Sho Miyahara 2018

set(srcs
  testMotionController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" motionController_srcs)
set(motionController_srcs ${motionController_srcs} PARENT_SCOPE)
