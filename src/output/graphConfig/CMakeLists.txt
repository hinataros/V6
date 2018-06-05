# @author Sho Miyahara 2018

add_subdirectory(activate)
add_subdirectory(modelGraphConfig)
add_subdirectory(controllerGraphConfig)

set(graphConfig_srcs ${graphConfig_srcs}
  ${activate_srcs}
  ${modelGraphConfig_srcs}
  ${controllerGraphConfig_srcs}
  PARENT_SCOPE
  )
