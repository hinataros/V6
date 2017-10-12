add_subdirectory(interpolation)

if(rls_rlsDynamicsRTC)
add_subdirectory(rlsDynamics)
set(comp_srcs ${comp_srcs}
  ${interpolation_srcs}
  ${rlsDynamics_srcs}
  )

set(comp_srcs ${comp_srcs} PARENT_SCOPE)
endif(rls_rlsDynamicsRTC)

if(rls_rlsSimulator)
add_subdirectory(rlsVelocity)
add_subdirectory(rlsAcceleration)

set(srcs
  initialize.cpp
  controller.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controllerComp_srcs)

set(controllerComp_srcs ${controllerComp_srcs}
  ${interpolation_srcs}
  ${rlsVelocity_srcs}
  ${rlsAcceleration_srcs}
  PARENT_SCOPE
  )

endif(rls_rlsSimulator)
