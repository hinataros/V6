add_subdirectory(reference)
add_subdirectory(control)

set(srcs
  initialize.cpp
  initialValue.cpp
  rename.cpp
  resize.cpp
  reset.cpp
  readWork.cpp
  reconfigure.cpp
  decompose.cpp
  outputConfig.cpp
  rlsDynamics.cpp
  )

add_subdirectory(RTC)

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)
set(rlsDynamics_srcs
  ${reference_srcs}
  ${control_srcs}
  ${rlsDynamics_srcs}
  ${rtc_srcs}
  PARENT_SCOPE
  )
