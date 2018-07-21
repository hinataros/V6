set(srcs
  base.cpp
  mix.cpp
  centroidal.cpp
  others.cpp
  debug.cpp
  rename.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rename_srcs)
set(rename_srcs ${rename_srcs} PARENT_SCOPE)
