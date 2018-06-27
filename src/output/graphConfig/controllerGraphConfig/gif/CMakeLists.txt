# @author Sho Miyahara 2018

set(srcs
  indexPrint.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" gif_srcs)
set(gif_srcs ${gif_srcs} PARENT_SCOPE)
