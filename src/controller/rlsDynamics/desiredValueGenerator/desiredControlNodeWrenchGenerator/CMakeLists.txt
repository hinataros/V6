# @author Sho Miyahara 2017

set(srcs
  desiredControlNodeWrenchGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredControlNodeWrenchGenerator_srcs)
set(desiredControlNodeWrenchGenerator_srcs ${desiredControlNodeWrenchGenerator_srcs} PARENT_SCOPE)
