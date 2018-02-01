# @author Sho Miyahara 2017

set(srcs
  quadProgpp.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" solver_srcs)
set(solver_srcs ${solver_srcs} PARENT_SCOPE)
