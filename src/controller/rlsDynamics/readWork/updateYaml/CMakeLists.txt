# @author Sho Miyahara 2017

set(srcs
  checkNode.cpp
  intString.cpp
  intStringInt.cpp
  intStringString.cpp
  intStringIntString.cpp
  intStringStringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateYaml_srcs)
set(updateYaml_srcs ${updateYaml_srcs} PARENT_SCOPE)
