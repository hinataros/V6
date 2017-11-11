add_subdirectory(velocityController)
add_subdirectory(accelerationController)

set(srcs
  momentumController.cpp
  forceController.cpp
  torqueController.cpp
  control.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" control_srcs)
set(control_srcs
  ${velocityController_srcs}
  ${accelerationController_srcs}
  ${control_srcs}
  PARENT_SCOPE
  )
