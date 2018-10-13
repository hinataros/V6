# @author Sho Miyahara 2018

set(srcs
  readModel.cpp
  setInclude.cpp
  readBody.cpp
  readCnoid.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readYaml_srcs)
set(readYaml_srcs ${readYaml_srcs} PARENT_SCOPE)
