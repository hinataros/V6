# @author Sho Miyahara 2017

set(srcs
  dcmFBPI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" dcmFeedbackController_srcs)
set(dcmFeedbackController_srcs ${dcmFeedbackController_srcs} PARENT_SCOPE)
