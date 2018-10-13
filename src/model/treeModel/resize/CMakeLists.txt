# @author Sho Miyahara 2018

set(srcs
  resizeLink.cpp
  resizeAll.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" resize_srcs)
set(resize_srcs ${resize_srcs} PARENT_SCOPE)
