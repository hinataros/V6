# @author Sho Miyahara 2017

set(srcs
  desiredExternalWrenchGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredExternalWrenchGenerator_srcs)
set(desiredExternalWrenchGenerator_srcs ${desiredExternalWrenchGenerator_srcs} PARENT_SCOPE)
