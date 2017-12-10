add_subdirectory(readYaml)
add_subdirectory(checkYaml)

set(srcs
  readWork.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readWork_srcs)
set(readWork_srcs ${readYaml_srcs} ${checkYaml_srcs} ${readWork_srcs} PARENT_SCOPE)
