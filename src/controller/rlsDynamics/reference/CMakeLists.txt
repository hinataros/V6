# @author Sho Miyahara 2017

set(srcs
  comReference.cpp
  baseReference.cpp
  endEffectorReference.cpp
  externalWrenchReference.cpp
  reference.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" reference_srcs)
set(reference_srcs ${reference_srcs} PARENT_SCOPE)
