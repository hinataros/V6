# @author Sho Miyahara 2018

set(srcs
  stringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" checkUserSize_srcs)
set(checkUserSize_srcs ${checkUserSize_srcs} PARENT_SCOPE)
