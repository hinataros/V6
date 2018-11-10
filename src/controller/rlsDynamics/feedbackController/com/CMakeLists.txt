# @author Sho Miyahara 2018

set(srcs
  comPI.cpp
  comDcmControl.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" com_srcs)
set(com_srcs ${com_srcs} PARENT_SCOPE)
