# @author Sho Miyahara 2017

set(srcs
  readJointStateVector.cpp
  writeJointStateVector.cpp
  stateMatrixFilter.cpp
  readControlNodeValueVector.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" interface_srcs)
set(interface_srcs ${interface_srcs} PARENT_SCOPE)
