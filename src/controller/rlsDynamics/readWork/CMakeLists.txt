# @author Sho Miyahara 2017

add_subdirectory(readYaml)
add_subdirectory(updateSequence)

set(srcs
  readSequence.cpp
  readWork.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readWork_srcs)
set(readWork_srcs ${readYaml_srcs} ${updateSequence_srcs} ${readWork_srcs} PARENT_SCOPE)
