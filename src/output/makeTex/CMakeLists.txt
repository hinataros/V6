add_subdirectory(environment)

set(srcs
  makeSimInfo.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeTex_srcs)
set(makeTex_srcs ${makeTex_srcs}
  ${environment_srcs}
  PARENT_SCOPE
  )
