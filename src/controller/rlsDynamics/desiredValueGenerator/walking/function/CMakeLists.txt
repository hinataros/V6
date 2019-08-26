# @author Sho Miyahara 2018

set(srcs
  factorio.cpp
  findPolyParam.cpp
  intPow.cpp
  makePosBoundary.cpp
  maketMat.cpp
  makeCMat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" walkingFunction_srcs)
set(walkingFunction_srcs ${walkingFunction_srcs} PARENT_SCOPE)
