#@author Sho Miyahara 2017

set(srcs
  mapping.cpp
  triggerConfig.cpp
  configurationManager.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" configurationManager_srcs)
set(configurationManager_srcs ${configurationManager_srcs} PARENT_SCOPE)
