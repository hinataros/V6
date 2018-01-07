#@author Sho Miyahara 2017

set(srcs
  readState.cpp
  # writeInput.cpp
  objectRTC.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" objectRTCCore_srcs)
set(objectRTCCore_srcs ${objectRTCCore_srcs} PARENT_SCOPE)
