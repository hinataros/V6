# @author Sho Miyahara 2017

set(srcs
  velocityOutputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" velocityOutputConfig_srcs)
set(velocityOutputConfig_srcs ${velocityOutputConfig_srcs} PARENT_SCOPE)
