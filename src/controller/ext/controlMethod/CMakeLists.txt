# @author Sho Miyahara 2018

add_subdirectory(defaultController)
add_subdirectory(momentumController)
add_subdirectory(motionController)
add_subdirectory(forceController)
add_subdirectory(torqueController)
add_subdirectory(inverseDynamicsController)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlMethod_srcs)
set(controlMethod_srcs
  ${defaultController_srcs}
  ${momentumController_srcs}
  ${motionController_srcs}
  ${forceController_srcs}
  ${torqueController_srcs}
  ${inverseDynamicsController_srcs}
  ${controlMethod_srcs}
  PARENT_SCOPE
  )


