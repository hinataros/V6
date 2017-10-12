set(srcs
  analyticalDynamics.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" analyticalDynamics_srcs)
set(analyticalDynamics_srcs ${analyticalDynamics_srcs} PARENT_SCOPE)
