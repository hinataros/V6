add_subdirectory(interpolation)
add_subdirectory(rlsDynamics)

if(rls_rlsDynamicsRTC)
  set(rlsDynamicsRTC_srcs ${rlsDynamicsRTC_srcs}
    ${interpolation_srcs}
    ${rlsDynamics_srcs}
    ${rtc_srcs}
    PARENT_SCOPE
    )
endif(rls_rlsDynamicsRTC)

if(rls_rlsSimulator)
  set(srcs
    initialize.cpp
    controller.cpp
    )

  MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controller_srcs)

set(controller_srcs ${controller_srcs}
  ${interpolation_srcs}
  ${rlsDynamics_srcs}
  PARENT_SCOPE
  )
endif(rls_rlsSimulator)


