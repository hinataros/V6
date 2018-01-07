# @author Sho Miyahara 2017

set(srcs
  makeMinipage.cpp
  makeMinipageLimb.cpp
  makeFigureTex.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" environment_srcs)
set(environment_srcs ${environment_srcs} PARENT_SCOPE)
