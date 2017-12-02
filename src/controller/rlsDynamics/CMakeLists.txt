add_subdirectory(reference)
add_subdirectory(control)
add_subdirectory(index)
add_subdirectory(outputConfig)

set(srcs
  initialize.cpp
  initialValue.cpp
  rename.cpp
  resize.cpp
  reset.cpp
  readWork.cpp
  reconfigure.cpp
  decompose.cpp
  rlsDynamics.cpp
  )

if(rls_rlsDynamicsRTC)
  add_subdirectory(RTC)
  set(rlsDynamicsRTCCore_srcs ${rlsDynamicsRTCCore_srcs} PARENT_SCOPE)
endif(rls_rlsDynamicsRTC)

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)
set(rlsDynamics_srcs
  ${rlsDynamics_srcs}
  ${reference_srcs}
  ${control_srcs}
  ${index_srcs}
  ${outputConfig_srcs}
  PARENT_SCOPE
  )
