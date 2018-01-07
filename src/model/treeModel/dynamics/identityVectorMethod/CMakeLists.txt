# @author Sho Miyahara 2017

set(srcs
  recursiveNewtonEuler.cpp
  gravity.cpp
  identityVectorMethod.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" identityVectorMethod_srcs)
set(identityVectorMethod_srcs ${identityVectorMethod_srcs} PARENT_SCOPE)
