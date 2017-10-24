add_subdirectory(reference)
add_subdirectory(velocityController)

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
  rlsVelocity.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsVelocity_srcs)
set(rlsVelocity_srcs
  ${reference_srcs}
  ${velocityController_srcs}
  ${rlsVelocity_srcs}
  PARENT_SCOPE
  )
