set(srcs
  F2rp.cpp
  weight.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" add_srcs)
set(add_srcs ${add_srcs} PARENT_SCOPE)
