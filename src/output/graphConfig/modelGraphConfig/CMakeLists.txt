# @author Sho Miyahara 2018

add_subdirectory(graphConfig)

set(srcs
  treeModelGraphConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" modelGraphConfig_srcs)
set(modelGraphConfig_srcs ${modelGraphConfig_srcs}
  ${graphConfig_srcs}
  PARENT_SCOPE
  )
