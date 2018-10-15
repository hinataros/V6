# @author Sho Miyahara 2018

set(srcs
  setControlModelState.cpp
  # readSharedData.cpp
  # writeSharedData.cpp
  writeInput.cpp
  rlsDynamicsRTC.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamicsRTCCore_srcs)
set(rlsDynamicsRTCCore_srcs ${rlsDynamicsRTCCore_srcs} PARENT_SCOPE)
