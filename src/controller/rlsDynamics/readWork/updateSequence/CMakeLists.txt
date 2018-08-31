# @author Sho Miyahara 2017

add_subdirectory(updateValue)
add_subdirectory(updateVector)
add_subdirectory(updateDiagonalMatrix)

set(srcs
  checkNode.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" updateSequence_srcs)
set(updateSequence_srcs
  ${updateValue_srcs}
  ${updateVector_srcs}
  ${updateDiagonalMatrix_srcs}
  ${updateSequence_srcs}
  PARENT_SCOPE
  )
