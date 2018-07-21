set(srcs
  basis.cpp
  base.cpp
  mix.cpp
  decompose.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" decompose_srcs)
set(decompose_srcs ${decompose_srcs} PARENT_SCOPE)
