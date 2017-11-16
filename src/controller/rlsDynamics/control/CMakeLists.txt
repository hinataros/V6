add_subdirectory(velocityController)
add_subdirectory(accelerationController)
add_subdirectory(torqueController)

set(srcs
  momentumController.cpp
  forceController.cpp
  control.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" control_srcs)
set(control_srcs
  ${control_srcs}
  ${velocityController_srcs}
  ${accelerationController_srcs}
  ${torqueController_srcs}
  PARENT_SCOPE
  )
