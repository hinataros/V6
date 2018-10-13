# @author Sho Miyahara 2018

set(srcs
  setControlModelState.cpp
  # readSharedData.cpp
  # writeSharedData.cpp
  writeInput.cpp
  rlsDynamicsRTC.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rtc_srcs)
set(rtc_srcs ${rtc_srcs} PARENT_SCOPE)
