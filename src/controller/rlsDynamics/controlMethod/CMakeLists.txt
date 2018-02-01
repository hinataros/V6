#@author Sho Miyahara 2017

add_subdirectory(zeroController)
add_subdirectory(velocityController)
add_subdirectory(accelerationController)
add_subdirectory(momentumController)
add_subdirectory(forceController)
add_subdirectory(torqueController)
add_subdirectory(inverseDynamicsController)

set(srcs
  controlMethod.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlMethod_srcs)
set(controlMethod_srcs
  ${controlMethod_srcs}
  ${zeroController_srcs}
  ${velocityController_srcs}
  ${accelerationController_srcs}
  ${momentumController_srcs}
  ${forceController_srcs}
  ${torqueController_srcs}
  ${inverseDynamicsController_srcs}
  PARENT_SCOPE
  )
