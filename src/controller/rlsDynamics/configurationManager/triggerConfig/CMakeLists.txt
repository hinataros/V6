#@author Sho Miyahara 2018

set(srcs
  checkFootContact.cpp
  checkContact.cpp
  defaultStateTrigger.cpp
  sequenceTrigger.cpp
  continuousSequence.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" triggerConfig_srcs)
set(triggerConfig_srcs ${triggerConfig_srcs} PARENT_SCOPE)
