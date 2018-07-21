set(srcs
  transform.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" transform_srcs)
set(transform_srcs ${transform_srcs} PARENT_SCOPE)
