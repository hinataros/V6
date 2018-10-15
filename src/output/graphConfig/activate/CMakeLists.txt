# @author Sho Miyahara 2018

set(srcs
  makeGraph.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" activate_srcs)
set(activate_srcs ${activate_srcs} PARENT_SCOPE)
