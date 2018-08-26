# @author Sho Miyahara 2017

set(srcs
  externalWrenchReferenceFF.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" externalWrenchReference_srcs)
set(externalWrenchReference_srcs ${externalWrenchReference_srcs} PARENT_SCOPE)
