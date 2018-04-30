# @author Sho Miyahara 2018

add_subdirectory(graphConfig)

set(srcs
  velocityGraphConfig.cpp
  accelerationGraphConfig.cpp
  dynamicsGraphConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controllerGraphConfig_srcs)
set(controllerGraphConfig_srcs ${controllerGraphConfig_srcs}
  ${graphConfig_srcs}
  PARENT_SCOPE
  )
