# @author Sho Miyahara 2018

add_subdirectory(sharedMemory)
add_subdirectory(interpolation)
add_subdirectory(solver)
add_subdirectory(rlsDynamics)
add_subdirectory(object)

if(rls_ext)
  add_subdirectory(ext)
endif(rls_ext)

if(rls_rlsDynamicsRTC)
  set(rlsDynamicsRTC_srcs
    ${sharedMemory_srcs}
    ${interpolation_srcs}
    ${solver_srcs}
    ${rlsDynamics_srcs}
    ${ext_srcs}
    ${rlsDynamicsRTC_srcs}
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
  add_subdirectory(controller)
  # set(srcs
  #   )

  # MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controller_srcs)

  set(controller_srcs
    ${interpolation_srcs}
    ${solver_srcs}
    ${rlsDynamics_srcs}
    ${ext_srcs}
    ${controller_srcs}
    PARENT_SCOPE
    )
endif(rls_rlsSimulator)


