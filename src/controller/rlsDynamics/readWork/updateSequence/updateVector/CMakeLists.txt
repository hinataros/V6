# @author Sho Miyahara 2017

set(srcs
  intString.cpp
  intStringInt.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateVector_srcs)
set(updateVector_srcs ${updateVector_srcs} PARENT_SCOPE)
