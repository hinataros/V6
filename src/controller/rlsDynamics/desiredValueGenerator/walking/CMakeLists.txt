# @author Sho Miyahara 2018

add_subdirectory(function)

set(srcs
  finalize.cpp
  setModel.cpp
  setYamlInfo.cpp
  initialize.cpp
  resize.cpp
  readController.cpp
  resetMat.cpp
  createHTTrajectory.cpp
  setInitialDcmPosition.cpp
  setComPosition.cpp
  setEEPosition.cpp
  setNaturalFrequency.cpp
  setBoundary.cpp
  setExt.cpp
  ht.cpp
  htOscillate.cpp
  eht.cpp
  setWayPoint.cpp
  createVRPTrajectory.cpp
  htVRP.cpp
  createVRPTrajTopt.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" walking_srcs)
set(walking_srcs
${walking_srcs}
${walkingFunction_srcs}
PARENT_SCOPE)
