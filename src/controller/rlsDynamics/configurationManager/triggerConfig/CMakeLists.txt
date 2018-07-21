#@author Sho Miyahara 2017

set(srcs
  checkContact.cpp
  staticCheckContact.cpp
  ankleStratagy.cpp
  ankleHipStratagy.cpp
  walking.cpp
  walkHT.cpp
  triggerConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" triggerConfig_srcs)
set(triggerConfig_srcs ${triggerConfig_srcs} PARENT_SCOPE)
