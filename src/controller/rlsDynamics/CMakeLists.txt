# @author Sho Miyahara 2017

add_subdirectory(initialize)
add_subdirectory(configurationManager)
add_subdirectory(readWork)
add_subdirectory(update)
add_subdirectory(trajectoryGenerator)
add_subdirectory(reference)
add_subdirectory(controlMethod)
add_subdirectory(index)

add_subdirectory(add)

add_subdirectory(outputConfig)

set(srcs
  # finalize.cpp
  initialValue.cpp
  resize.cpp
  reconfigure.cpp
  rlsDynamics.cpp
  )

if(rls_rlsDynamicsRTC)
  add_subdirectory(RTC)
  set(rlsDynamicsRTCCore_srcs ${rlsDynamicsRTCCore_srcs} PARENT_SCOPE)
endif(rls_rlsDynamicsRTC)

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)

set(rlsDynamics_srcs
  ${rlsDynamics_srcs}
  ${initialize_srcs}
  ${configurationManager_srcs}
  ${readWork_srcs}
  ${update_srcs}
  ${trajectoryGenerator_srcs}
  ${reference_srcs}
  ${controlMethod_srcs}
  ${index_srcs}
  ${add_srcs}
  ${transform_srcs}
  ${outputConfig_srcs}
  PARENT_SCOPE
  )
