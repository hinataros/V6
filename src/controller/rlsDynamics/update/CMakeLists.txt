add_subdirectory(transform)
add_subdirectory(decompose)
add_subdirectory(rename)

set(srcs
  objective.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" update_srcs)
set(update_srcs
  ${transform_srcs}
  ${decompose_srcs}
  ${rename_srcs}
  ${update_srcs}
  PARENT_SCOPE
  )
