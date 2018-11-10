# @author Sho Miyahara 2018

set(srcs
  setModel.cpp
  setYamlInfo.cpp
  initialize.cpp
  resize.cpp
  readController.cpp
  reset.cpp
  createHTTrajectory.cpp
  createExtHTTrajectory.cpp
  setInitialDcmPosition.cpp
  setComPosition.cpp
  setBoundary.cpp
  setExtForce.cpp
  ht.cpp
  extht.cpp
  eht.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" walking_srcs)
set(walking_srcs ${walking_srcs} PARENT_SCOPE)
