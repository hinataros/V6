#@author Sho Miyahara 2018

add_subdirectory(triggerConfig)

set(srcs
  trigger.cpp
  mapping.cpp
  configurationManager.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" configurationManager_srcs)
set(configurationManager_srcs ${triggerConfig_srcs} ${configurationManager_srcs} PARENT_SCOPE)
