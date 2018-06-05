# @author Sho Miyahara 2018

set(srcs
  accelerationGraphConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationGraphConfig_srcs)
set(accelerationGraphConfig_srcs ${accelerationGraphConfig_srcs} PARENT_SCOPE)
