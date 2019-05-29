set(srcs
  F2rp.cpp
  h_weight.cpp
  computeBWC.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" others_srcs)
set(others_srcs ${others_srcs} PARENT_SCOPE)
