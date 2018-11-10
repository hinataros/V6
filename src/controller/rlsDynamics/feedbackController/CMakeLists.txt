# @author Sho Miyahara 2018

add_subdirectory(_initialize)
add_subdirectory(baseTranslation)
add_subdirectory(baseRotation)
add_subdirectory(com)
add_subdirectory(dcm)
add_subdirectory(controlNodeMotion)
add_subdirectory(controlNodeForce)
add_subdirectory(externalWrench)
add_subdirectory(others)
add_subdirectory(_feedbackController)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" feedbackController_srcs)

set(feedbackController_srcs
  ${initialize_srcs}
  ${baseTranslation_srcs}
  ${baseRotation_srcs}
  ${com_srcs}
  ${dcm_srcs}
  ${controlNodeMotion_srcs}
  ${controlNodeForce_srcs}
  ${externalWrench_srcs}
  ${others_srcs}
  ${feedbackController_srcs}
  PARENT_SCOPE
  )
