add_subdirectory(reference)
add_subdirectory(accelerationController)

set(srcs
  initialize.cpp
  initialValue.cpp
  rename.cpp
  resize.cpp
  reset.cpp
  readWork.cpp
  reconfigure.cpp
  decompose.cpp
  outputConfig.cpp
  rlsAcceleration.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsAcceleration_srcs)
set(rlsAcceleration_srcs
  ${reference_srcs}
  ${accelerationController_srcs}
  ${rlsAcceleration_srcs}
  PARENT_SCOPE
  )
