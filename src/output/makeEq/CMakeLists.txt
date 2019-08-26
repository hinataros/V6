# @author Sho Miyahara 2017

set(srcs
  makeEquationTex.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeEq_srcs)
set(makeEq_srcs ${makeEq_srcs} PARENT_SCOPE)
