# @author Sho Miyahara 2018

add_subdirectory(model)
add_subdirectory(yamlInfo)
add_subdirectory(configurationManager)
add_subdirectory(desiredValueGenerator)
add_subdirectory(feedbackController)
add_subdirectory(readController)
add_subdirectory(update)
add_subdirectory(controlMethod)
add_subdirectory(outputConfig)

# add_subdirectory(extWrapper)

add_subdirectory(rlsDynamics)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)

set(rlsDynamics_srcs
  ${initialize_srcs}
  ${model_srcs}
  ${yamlInfo_srcs}
  ${configurationManager_srcs}
  ${desiredValueGenerator_srcs}
  ${feedbackController_srcs}
  ${readController_srcs}
  ${update_srcs}
  ${controlMethod_srcs}
  ${index_srcs}
  ${transform_srcs}
  ${outputConfig_srcs}
  ${extWrapper_srcs}
  ${rlsDynamics_srcs}
  PARENT_SCOPE
  )
