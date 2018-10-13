# @author Sho Miyahara 2018

add_subdirectory(defaultController)
add_subdirectory(operationalSpaceVelocityController)
add_subdirectory(configurationSpaceVelocityController)
add_subdirectory(operationalSpaceAccelerationController)
add_subdirectory(configurationSpaceAccelerationController)
add_subdirectory(momentumController)
add_subdirectory(internalForceController)
add_subdirectory(forceController)
add_subdirectory(torqueController)
add_subdirectory(inverseDynamicsController)

add_subdirectory(externalWrenchController)
add_subdirectory(others)

set(srcs
  controlMethod.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlMethod_srcs)
set(controlMethod_srcs
  ${controlMethod_srcs}
  ${defaultController_srcs}
  ${operationalSpaceVelocityController_srcs}
  ${configurationSpaceVelocityController_srcs}
  ${operationalSpaceAccelerationController_srcs}
  ${configurationSpaceAccelerationController_srcs}
  ${momentumController_srcs}
  ${internalForceController_srcs}
  ${forceController_srcs}
  ${torqueController_srcs}
  ${inverseDynamicsController_srcs}
  ${externalWrenchController_srcs}
  ${others_srcs}
  PARENT_SCOPE
  )
