# @author Sho Miyahara 2018

set(srcs
  velocityGraphConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" velocityGraphConfig_srcs)
set(velocityGraphConfig_srcs ${velocityGraphConfig_srcs} PARENT_SCOPE)
