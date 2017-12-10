set(srcs
  checkNode.cpp
  checkValue.cpp
  checkVector.cpp
  checkMatrix.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" checkYaml_srcs)
set(checkYaml_srcs ${readYaml_srcs} ${checkYaml_srcs} PARENT_SCOPE)
