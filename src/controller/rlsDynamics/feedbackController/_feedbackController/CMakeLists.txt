# @author Sho Miyahara 2018

set(srcs
  mapping.cpp
  readController.cpp
  stack.cpp
  feedbackController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" feedbackController_srcs)

set(feedbackController_srcs ${feedbackController_srcs} PARENT_SCOPE)
