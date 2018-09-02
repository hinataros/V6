# @author Sho Miyahara 2017

set(srcs
  readModel.cpp
  setDir.cpp
  readBody.cpp
  setInfo.cpp
  readCnoid.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readYaml_srcs)
set(readYaml_srcs ${readYaml_srcs} PARENT_SCOPE)
