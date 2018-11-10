# @author Sho Miyahara 2018

set(srcs
  controlNodeMomentCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeMoment_srcs)
set(controlNodeMoment_srcs ${controlNodeMoment_srcs} PARENT_SCOPE)
