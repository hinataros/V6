# @author Sho Miyahara 2018

set(srcs
  controlNodeForceFBFF.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeForceFeedbackController_srcs)
set(controlNodeForceFeedbackController_srcs ${controlNodeForceFeedbackController_srcs} PARENT_SCOPE)
