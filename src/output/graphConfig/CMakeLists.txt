# @author Sho Miyahara 2018

# add_subdirectory(activate)
# add_subdirectory(modelGraphConfig)
add_subdirectory(funcGraphConfig)

set(srcs
  makeGraph.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" graphConfig_srcs)
set(graphConfig_srcs
  ${activate_srcs}
  ${funcGraphConfig_srcs}
  # ${controllerGraphConfig_srcs}
  ${graphConfig_srcs}
  PARENT_SCOPE
  )
