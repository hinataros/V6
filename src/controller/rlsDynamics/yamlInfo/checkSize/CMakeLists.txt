# @author Sho Miyahara 2018

set(srcs
  string.cpp
  stringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" checkSize_srcs)
set(checkSize_srcs ${checkSize_srcs} PARENT_SCOPE)
