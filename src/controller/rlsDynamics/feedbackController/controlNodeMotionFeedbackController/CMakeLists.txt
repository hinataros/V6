# @author Sho Miyahara 2018

set(srcs
  controlNodeMotionFBPI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeMotionFeedbackController_srcs)
set(controlNodeMotionFeedbackController_srcs ${controlNodeMotionFeedbackController_srcs} PARENT_SCOPE)
