# @author Sho Miyahara 2018

set(srcs
  string.cpp
  stringString.cpp
  stringStringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" checkUserValue_srcs)
set(checkUserValue_srcs ${checkUserValue_srcs} PARENT_SCOPE)
