# @author Sho Miyahara 2017

set(srcs
  checkNode.cpp
  updateValue.cpp
  updateVector.cpp
  updateDiagonalMatrix.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateSequence_srcs)
set(updateSequence_srcs ${updateSequence_srcs} PARENT_SCOPE)
