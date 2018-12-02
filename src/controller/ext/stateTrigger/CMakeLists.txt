# @author Sho Miyahara 2018

set(srcs
  default.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" stateTrigger_srcs)
set(stateTrigger_srcs ${stateTrigger_srcs} PARENT_SCOPE)


