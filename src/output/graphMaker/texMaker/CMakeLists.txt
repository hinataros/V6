# @author Sho Miyahara 2018

set(srcs
  interfaceMaker.cpp
  texMaker.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" texMaker_srcs)
set(texMaker_srcs ${texMaker_srcs} PARENT_SCOPE)
