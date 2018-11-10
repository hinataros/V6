# @author Sho Miyahara 2018

set(srcs
  string.cpp
  stringString.cpp
  stringStringString.cpp
  stringStringStringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" checkValue_srcs)
set(checkValue_srcs ${checkValue_srcs} PARENT_SCOPE)
