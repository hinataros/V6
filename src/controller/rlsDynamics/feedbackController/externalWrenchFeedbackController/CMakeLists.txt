# @author Sho Miyahara 2018

set(srcs
  externalWrenchFBFF.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" externalWrenchFeedbackController_srcs)
set(externalWrenchFeedbackController_srcs ${externalWrenchFeedbackController_srcs} PARENT_SCOPE)
