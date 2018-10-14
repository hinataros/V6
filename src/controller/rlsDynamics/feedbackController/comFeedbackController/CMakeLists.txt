# @author Sho Miyahara 2018

set(srcs
  comFBPI.cpp
  comFBDcmControl.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" comFeedbackController_srcs)
set(comFeedbackController_srcs ${comFeedbackController_srcs} PARENT_SCOPE)
