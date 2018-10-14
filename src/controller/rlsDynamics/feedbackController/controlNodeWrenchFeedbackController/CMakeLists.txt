# @author Sho Miyahara 2018

set(srcs
  controlNodeWrenchFBFF.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeWrenchFeedbackController_srcs)
set(controlNodeWrenchFeedbackController_srcs ${controlNodeWrenchFeedbackController_srcs} PARENT_SCOPE)
