# @author Sho Miyahara 2017

set(srcs
  controlNodeReferencePI.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeReference_srcs)
set(controlNodeReference_srcs ${controlNodeReference_srcs} PARENT_SCOPE)
