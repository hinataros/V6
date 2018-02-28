# @author Sho Miyahara 2017

set(srcs
  endEffectorSequence.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" endEffectorReference_srcs)
set(endEffectorReference_srcs ${endEffectorReference_srcs} PARENT_SCOPE)
