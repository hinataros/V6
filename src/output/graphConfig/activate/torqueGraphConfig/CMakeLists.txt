# @author Sho Miyahara 2018

set(srcs
  masterGraphConfig.cpp
  torqueGraphConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" torqueGraphConfig_srcs)
set(torqueGraphConfig_srcs ${torqueGraphConfig_srcs} PARENT_SCOPE)
