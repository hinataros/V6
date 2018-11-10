# @author Sho Miyahara 2018

set(srcs
  readJointState.cpp
  writeJointState.cpp
  readSensorNodeValue.cpp
  writeSensorNodeValue.cpp
  stateMatrixFilter.cpp
  readControlNodeValue.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" interface_srcs)
set(interface_srcs ${interface_srcs} PARENT_SCOPE)
