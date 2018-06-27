# @author Sho Miyahara 2017

set(srcs
  accelerationOutputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationOutputConfig_srcs)
set(accelerationOutputConfig_srcs ${accelerationOutputConfig_srcs} PARENT_SCOPE)
