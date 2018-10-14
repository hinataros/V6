# @author Sho Miyahara 2018

set(srcs
  baseTranslationFBPI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseTranslationFeedbackController_srcs)
set(baseTranslationFeedbackController_srcs ${baseTranslationFeedbackController_srcs} PARENT_SCOPE)
