set(srcs
  decompose.cpp
  objective.cpp
  rename.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" update_srcs)
set(update_srcs ${update_srcs} PARENT_SCOPE)
