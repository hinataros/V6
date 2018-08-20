# @author Sho Miyahara 2017

# add_subdirectory(sharedMemory)
# add_subdirectory(interpolation)
# add_subdirectory(solver)
add_subdirectory(rlsDynamics)
# add_subdirectory(object)

if(rls_rlsDynamicsRTC)
  set(rlsDynamicsRTC_srcs ${rlsDynamicsRTC_srcs}
    ${sharedMemory_srcs}
    ${interpolation_srcs}
    ${solver_srcs}
    ${rlsDynamics_srcs}
    ${rlsDynamicsRTCCore_srcs}
    PARENT_SCOPE
    )
endif(rls_rlsDynamicsRTC)

if(rls_objectRTC)
  set(objectRTC_srcs ${objectRTC_srcs}
    ${sharedMemory_srcs}
    ${objectRTCCore_srcs}
    PARENT_SCOPE
    )
endif(rls_objectRTC)

if(rls_rlsSimulator)
  # set(srcs
  #   initialize.cpp
  #   finalize.cpp
  #   controller.cpp
  #   )

  # MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controller_srcs)

  set(controller_srcs ${controller_srcs}
    ${interpolation_srcs}
    ${solver_srcs}
    ${rlsDynamics_srcs}
    PARENT_SCOPE
    )
endif(rls_rlsSimulator)


