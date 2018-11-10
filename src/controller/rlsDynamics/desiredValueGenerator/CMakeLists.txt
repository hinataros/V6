# @author Sho Miyahara 2018

add_subdirectory(_initialize)
add_subdirectory(baseTranslation)
add_subdirectory(baseRotation)
add_subdirectory(controlNodeTranslation)
add_subdirectory(controlNodeRotation)
add_subdirectory(controlNodeForce)
add_subdirectory(controlNodeMoment)
add_subdirectory(com)
add_subdirectory(dcm)
add_subdirectory(externalWrench)
add_subdirectory(default)
add_subdirectory(_desiredValueGenerator)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" Value_srcs)

set(desiredValueGenerator_srcs
  ${initialize_srcs}
  ${baseTranslation_srcs}
  ${baseRotation_srcs}
  ${controlNodeTranslation_srcs}
  ${controlNodeRotation_srcs}
  ${controlNodeForce_srcs}
  ${controlNodeMoment_srcs}
  ${com_srcs}
  ${dcm_srcs}
  ${externalWrench_srcs}
  ${default_srcs}
  ${desiredValueGenerator_srcs}
  PARENT_SCOPE
  )
