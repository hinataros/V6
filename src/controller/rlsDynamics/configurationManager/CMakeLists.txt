#@author Sho Miyahara 2017

add_subdirectory(triggerConfig)

set(srcs
  update.cpp
  trigger.cpp
  mapping.cpp
  configurationManager.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" configurationManager_srcs)
set(configurationManager_srcs ${configurationManager_srcs} ${triggerConfig_srcs} PARENT_SCOPE)
