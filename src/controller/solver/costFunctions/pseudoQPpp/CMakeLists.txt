# @author Sho Miyahara 2017

set(srcs
  costConfiguration.cpp
  costFunctionQPpp.cpp
  initialSearcher.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" pseudoQPpp_srcs)
set(pseudoQPpp_srcs ${pseudoQPpp_srcs} PARENT_SCOPE)
