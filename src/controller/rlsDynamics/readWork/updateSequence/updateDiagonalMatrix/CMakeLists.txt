# @author Sho Miyahara 2017

set(srcs
  intString.cpp
  intStringInt.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateDiagonalMatrix_srcs)
set(updateDiagonalMatrix_srcs ${updateDiagonalMatrix_srcs} PARENT_SCOPE)
