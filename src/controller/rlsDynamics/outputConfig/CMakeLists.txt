# @author Sho Miyahara 2017

set(srcs
  velocityOutputConfig.cpp
  accelerationOutputConfig.cpp
  torqueOutputConfig.cpp
  outputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" outputConfig_srcs)
set(outputConfig_srcs ${outputConfig_srcs} PARENT_SCOPE)
