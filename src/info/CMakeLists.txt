# @author Sho Miyahara 2017

set(srcs
  initialize.cpp
  finalize.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" info_srcs)
set(info_srcs ${info_srcs} PARENT_SCOPE)
