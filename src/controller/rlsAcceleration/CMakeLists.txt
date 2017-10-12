set(srcs
  initialize.cpp
  initialValue.cpp
  rename.cpp
  resize.cpp
  reset.cpp
  readWork.cpp
  reconfigure.cpp
  decompose.cpp
  baseReference.cpp
  endEffectorReference.cpp
  accelerationController.cpp
  outputConfig.cpp
  rlsAcceleration.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsAcceleration_srcs)
set(rlsAcceleration_srcs ${rlsAcceleration_srcs} PARENT_SCOPE)
