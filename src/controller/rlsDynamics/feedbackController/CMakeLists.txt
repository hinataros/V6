# @author Sho Miyahara 2017

add_subdirectory(baseTranslationFeedbackController)
add_subdirectory(baseOrientationFeedbackController)
add_subdirectory(comFeedbackController)
add_subdirectory(dcmFeedbackController)
add_subdirectory(controlNodeAccelerationFeedbackController)
add_subdirectory(controlNodeWrenchFeedbackController)
add_subdirectory(externalWrenchFeedbackController)

set(srcs
  spatialFeedbackController.cpp
  feedbackController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" feedbackController_srcs)
set(feedbackController_srcs
  ${baseTranslationFeedbackController_srcs}
  ${baseOrientationFeedbackController_srcs}
  ${comFeedbackController_srcs}
  ${dcmFeedbackController_srcs}
  ${controlNodeAccelerationFeedbackController_srcs}
  ${controlNodeWrenchFeedbackController_srcs}
  ${externalWrenchFeedbackController_srcs}
  ${feedbackController_srcs}
  PARENT_SCOPE
  )
