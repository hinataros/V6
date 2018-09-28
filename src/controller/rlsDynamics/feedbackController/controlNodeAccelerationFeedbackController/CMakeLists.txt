# @author Sho Miyahara 2017

set(srcs
  controlNodeAccelerationFBPI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeAccelerationFeedbackController_srcs)
set(controlNodeAccelerationFeedbackController_srcs ${controlNodeAccelerationFeedbackController_srcs} PARENT_SCOPE)
