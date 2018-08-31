# @author Sho Miyahara 2017

set(srcs
  intString.cpp
  intStringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateValue_srcs)
set(updateValue_srcs ${updateValue_srcs} PARENT_SCOPE)
