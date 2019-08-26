# @author Sho Miyahara 2017

set(srcs
  costConfiguration.cpp
  costFunction.cpp
  initialSearcher.cpp
  functions.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" postureGenerator_srcs)
set(pgsolver_srcs ${postureGenerator_srcs} PARENT_SCOPE)
