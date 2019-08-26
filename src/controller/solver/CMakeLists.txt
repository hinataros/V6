# @author Sho Miyahara 2017

add_subdirectory(costFunctions)

set(srcs
  quadProgpp.cpp
  judgement.cpp
  CFSQP.cpp
  cfsqp.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" solver_srcs)
set(solver_srcs
${solver_srcs}
${costFunctions_srcs}
PARENT_SCOPE)
