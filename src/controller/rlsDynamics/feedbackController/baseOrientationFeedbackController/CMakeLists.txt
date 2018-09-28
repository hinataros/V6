# @author Sho Miyahara 2017

set(srcs
  baseOrientationFBPI.cpp
  # baseOrientationAnkleHip.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseOrientationFeedbackController_srcs)
set(baseOrientationFeedbackController_srcs ${baseOrientationFeedbackController_srcs} PARENT_SCOPE)
