# @author Sho Miyahara 2018

set(srcs
  setModel.cpp
  setYamlInfo.cpp
  initialize.cpp
  resize.cpp
  readController.cpp
  reset.cpp
  createHTTrajectory.cpp
  setInitialDcmPosition.cpp
  setComPosition.cpp
  setBoundary.cpp
  ht.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" walking_srcs)
set(walking_srcs ${walking_srcs} PARENT_SCOPE)
