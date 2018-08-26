# @author Sho Miyahara 2017

add_subdirectory(kinematics)
add_subdirectory(dynamics)

set(srcs
  readJointStateVector.cpp
  writeJointStateVector.cpp
  stateMatrixFilter.cpp
  readEndEffectorValueVector.cpp
  readBody.cpp
  # readModel.cpp
  readCnoid.cpp
  initializeInfo.cpp
  initializeLink.cpp
  initializeAll.cpp
  # outputConfig.cpp
  # deleteModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" treeModel_srcs)
set(treeModel_srcs ${treeModel_srcs}
  ${kinematics_srcs}
  ${dynamics_srcs}
  PARENT_SCOPE
  )
