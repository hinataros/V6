# @author Sho Miyahara 2017

add_subdirectory(velocityOutputConfig)
add_subdirectory(accelerationOutputConfig)
add_subdirectory(torqueOutputConfig)

set(srcs
  outputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" outputConfig_srcs)
set(outputConfig_srcs
  ${outputConfig_srcs}
  ${velocityOutputConfig_srcs}
  ${accelerationOutputConfig_srcs}
  ${torqueOutputConfig_srcs}
  PARENT_SCOPE
  )
