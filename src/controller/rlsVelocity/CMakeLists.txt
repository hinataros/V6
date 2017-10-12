set(srcs
  initialize.cpp
  initialValue.cpp
  resize.cpp
  reset.cpp
  readWork.cpp
  reconfigure.cpp
  baseReference.cpp
  endEffectorReference.cpp
  decompose.cpp
  velocityController.cpp
  outputConfig.cpp
  rlsVelocity.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsVelocity_srcs)
set(rlsVelocity_srcs ${rlsVelocity_srcs} PARENT_SCOPE)
